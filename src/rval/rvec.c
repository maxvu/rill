#include "config/alloc.h"
#include "config/rerr.h"
#include "rval/rvec.h"
#include "rval/rval.h"

#include <string.h>

rval rvecq () {
    rval tmp = rnil();
    rvec_init( &tmp, RILL_RVEC_DEFSIZ );
    return tmp;
}

int rvec_realloc ( rval * vecval, size_t new_cap ) {
    rval tmp = rnil();
    if ( !rvec_init( &tmp, new_cap ) )
        return 0;
    memcpy( tmp.vec->vls, vecval->vec->vls, sizeof( rval ) * vecval->vec->len );
    tmp.vec->len = vecval->vec->len;
    RILL_DEALLOC( vecval->vec );
    vecval->vec = tmp.vec;
    return 1;
}

int rvec_init ( rval * val, size_t cap ) {
    if ( !val )
        return 0;
    if ( rval_type( val ) == RVT_VEC ) {
        if ( !rvec_reserve( val, cap ) )
            return 0;
        rvec_clear( val );
        return 1;
    }
    if ( cap < RILL_RVEC_MINSIZ )
        cap = RILL_RVEC_MINSIZ;
    rvec * vec = RILL_ALLOC( sizeof( rvec ) + sizeof( rval ) * cap );
    if ( !vec ) {
        rerr_set( RILL_ERR_ALLOC );
        return 0;
    }
    *vec = ( rvec ) {
        .len = 0,
        .cap = cap,
        .ref = 1
    };
    for ( size_t i = 0; i < cap; i++ )
        *( vec->vls + i ) = rnil();
    rval_release( val );
    *val = ( rval ) {
        .typ = RVT_VEC,
        .vec = vec
    };
    return 1;
}

size_t rvec_len ( rval * vecval ) {
    RILL_ASSERT_ISVEC( vecval );
    return vecval->vec->len;
}

int rvec_reserve ( rval * vecval, size_t cap ) {
    RILL_ASSERT_ISVEC( vecval );
    rvec * vec = vecval->vec;
    if ( vec->cap >= cap )
        return 1;
    return rvec_realloc( vecval, cap );
}

int rvec_compact ( rval * vecval ) {
    RILL_ASSERT_ISVEC( vecval );
    rvec * vec = vecval->vec;
    size_t target = vec->len;
    if ( target < RILL_RVEC_MINSIZ )
        target = RILL_RVEC_MINSIZ;
    if ( target == vec->cap )
        return 1;
    return rvec_realloc( vecval, target );
}

int rvec_clone ( rval * dst, rval * src ) {
    RILL_ASSERT_ARGNOTNULL( dst );
    RILL_ASSERT_ISVEC( src );
    rval tmp = rnil();
    if ( !rvec_init( &tmp, rvec_len( src ) ) )
        return 0;
    for ( size_t i = 0; i < src->vec->len; i++ ) {
        if ( !rval_clone( tmp.vec->vls + i, src->vec->vls + i ) ) {
            rval_release( &tmp );
            return 0;
        }
    }
    rval_move( dst, &tmp );
    return 1;
}

int rvec_exclude ( rval * vecval ) {
    RILL_ASSERT_ISVEC( vecval );
    return rvec_realloc( vecval, rvec_len( vecval ) );
}

int rvec_release ( rval * vecval ) {
    RILL_ASSERT_ISVEC( vecval );
    rvec * vec = vecval->vec;
    if ( --vec->ref )
        return 1;
    for ( size_t i = 0; i < vec->len; i++ )
        rval_release( vec->vls + i );
    RILL_DEALLOC( vec );
    *vecval = rnil();
    return 1;
}

int rvec_push ( rval * vecval, rval * item ) {
    RILL_ASSERT_ISVEC( vecval );
    RILL_ASSERT_ARGNOTNULL( item );
    if ( vecval->vec->len == vecval->vec->cap )
        if ( !rvec_reserve(
                vecval,
                RILL_RVEC_GROWTH * ( double ) vecval->vec->cap
            )
        ) return 0;
    if ( vecval->vec->ref > 1 || rval_cyclesto( item, vecval ) )
        if ( !rval_exclude( vecval ) )
            return 0;
    rval_copy( vecval->vec->vls + vecval->vec->len, item );
    vecval->vec->len++;
    return 1;
}

int rvec_pop ( rval * vecval ) {
    RILL_ASSERT_ISVEC( vecval );
    if ( !rvec_len( vecval ) )
        return 0;
    rvec * vec = vecval->vec;
    if ( vec->ref > 1 && !rval_exclude( vecval ) )
        return 0;
    vec = vecval->vec;
    rval_release( vec->vls + vec->len - 1 );
    vec->len--;
    return 1;
}

rval * rvec_get ( rval * vecval, size_t idx ) {
    RILL_ASSERT_ISVEC( vecval );
    rvec * vec = vecval->vec;
    if ( idx >= vec->len )
        return NULL;
    return vec->vls + idx;
}

int rvec_set ( rval * vecval, size_t idx, rval * item ) {
    RILL_ASSERT_ISVEC( vecval );
    RILL_ASSERT_ARGNOTNULL( item );
    rvec * vec = vecval->vec;
    if ( idx >= vec->len )
        return 0;
    if ( vec->ref > 1 || rval_cyclesto( item, vecval ) )
        if ( !rval_exclude( vecval ) )
            return 0;
    vec = vecval->vec;
    rval_copy( vec->vls + idx, item );
    return 1;
}

int rvec_fill ( rval * vecval, rval * item, size_t n ) {
    RILL_ASSERT_ISVEC( vecval );
    RILL_ASSERT_ARGNOTNULL( item );
    rvec * vec = vecval->vec;
    if ( vec->cap < n )
        if ( !rvec_reserve( vecval, RILL_RVEC_GROWTH * vec->cap ) )
            return 0;
    if ( vec->ref > 1 || rval_cyclesto( item, vecval ) )
        if ( !rval_exclude( vecval ) )
            return 0;
    vec = vecval->vec;
    for ( size_t i = 0; i < n; i++ )
        if ( !rval_copy( vec->vls + i, item ) )
            return 0;
    vec->len = n;
    return 1;
}

int rvec_reverse ( rval * vecval ) {
    RILL_ASSERT_ISVEC( vecval );
    rvec * vec = vecval->vec;
    if ( vec->ref > 1 && !rval_exclude( vecval ) )
        return 0;
    vec = vecval->vec;
    for ( size_t i = 0; i < vec->len / 2; i++ )
        rval_swap( vec->vls + i, vec->vls + ( vec->len - 1 - i ) );
    return 1;
}

int rvec_concat ( rval * dstval, rval * srcval ) {
    RILL_ASSERT_ISVEC( srcval );
    RILL_ASSERT_ISVEC( dstval );
    rval tmp = rnil();
    if ( !rvec_init( &tmp, rvec_len( dstval ) + rvec_len( srcval ) ) )
        return 0;
    for ( size_t i = 0; i < rvec_len( dstval ); i++ ) {
        if ( !rvec_push( &tmp, dstval->vec->vls + i ) ) {
            rval_release( &tmp );
            return 0;
        }
    }
    for ( size_t i = 0; i < rvec_len( srcval ); i++ ) {
        if ( !rvec_push( &tmp, srcval->vec->vls + i ) ) {
            rval_release( &tmp );
            return 0;
        }
    }
    rval_move( dstval, &tmp );
    return 1;
}

int rvec_clear ( rval * vecval ) {
    RILL_ASSERT_ISVEC( vecval );
    rvec * vec = vecval->vec;
    if ( vec->ref > 1 && !rval_exclude( vecval ) )
        return 0;
    vec = vecval->vec;
    for ( size_t i = 0; i < vec->len; i++ )
        rval_release( vec->vls + i );
    vec->len = 0;
    return 1;
}

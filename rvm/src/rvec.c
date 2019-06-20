#include "rerr.h"
#include "rvec.h"
#include "rval.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

rval rvecq ( size_t init_cap ) {
    rval tmp = rnil();
    if ( init_cap < RVEC_DEFAULT_SIZE )
        init_cap = RVEC_DEFAULT_SIZE;
    rvec_init( &tmp, init_cap );
    return tmp;
}

rerr rvec_init ( rval * val, size_t cap ) {
    ASSERT_NOT_NULL( val );
    if ( IS_VEC( val ) )
        return rvec_reserve( val, cap );
    if ( cap < RVEC_MINIMUM_SIZE )
        cap = RVEC_MINIMUM_SIZE;
    rval * vls = ( rval * ) malloc( sizeof( rval ) * cap );
    if ( !vls )
        return RERR_SYS_ALLOC;
    rvec * vec = ( rvec * ) malloc ( sizeof( rvec ) );
    if ( !vec ) {
        free( vls );
        return RERR_SYS_ALLOC;
    }
    memset( vls, 0, sizeof( rval ) * cap );
    *vec = ( rvec ) {
        .ref = 1,
        .vls = vls,
        .len = 0,
        .cap = cap
    };
    *val = ( rval ) {
        .info = RVT_VEC,
        .vec = vec
    };
    return RERR_OK;
}

size_t rvec_len ( rval * val ) {
    ASSERT_VEC( val );
    return val->vec->len;
}

rerr rvec_clone ( rval * dst, rval * src ) {
    ASSERT_NOT_NULL( dst );
    ASSERT_VEC( src );
    rval tmp = rnil();
    ASSERT_OK( rvec_init( &tmp, src->vec->len ) );
    rvec * a = tmp.vec;
    rvec * b = src->vec;
    memcpy( a->vls, b->vls, sizeof( rval ) * b->len );
    for ( size_t i = 0; i < b->len; i++ )
        rval_lease( a->vls );
    rval_move( dst, &tmp );
    return RERR_OK;
}

rerr rvec_resize ( rval * val, size_t new_cap ) {
    if ( new_cap < val->vec->len )
        return RERR_USE_OOB;
    rval * new_vls = ( rval * ) malloc( sizeof( rval ) * new_cap );
    if ( !new_vls )
        return RERR_SYS_ALLOC;
    memcpy( new_vls, val->vec->vls, sizeof( rval ) * val->vec->len );
    {
        size_t i = new_cap;
        size_t j = val->vec->len;
        size_t diff = i < j ? j - i : i - j;
        memset( new_vls + j, 0, diff * sizeof( rval ) );
    }
    free( val->vec->vls );
    val->vec->vls = new_vls;
    val->vec->cap = new_cap;
    return RERR_OK;
}

rerr rvec_reserve ( rval * val, size_t new_cap ) {
    ASSERT_VEC( val );
    if ( val->vec->cap >= new_cap )
        return RERR_OK;
    return rvec_resize( val, new_cap );
}

rerr rvec_compact ( rval * val ) {
    ASSERT_VEC( val );
    size_t target = val->vec->len;
    if ( target <= RVEC_MINIMUM_SIZE )
        target = RVEC_MINIMUM_SIZE;
    return rvec_resize( val, target );
}

rerr rvec_push ( rval * val, rval * item ) {
    ASSERT_VEC( val );
    ASSERT_NOT_NULL( item );
    ASSERT_OK( rval_exclude( val ) );
    ASSERT_OK( rvec_reserve( val, val->vec->len + 1 ) );
    if ( rval_cyclesto( val, item ) )
        ASSERT_OK( rval_clone( val, val ) );
    ASSERT_OK( rval_copy( val->vec->vls + val->vec->len++, item ) );
    return RERR_OK;
}

rerr rvec_pop ( rval * val ) {
    ASSERT_VEC( val );
    ASSERT_OK( rval_exclude( val ) );
    if ( !val->vec->len )
        return RERR_USE_OOB;
    val->vec->len -= 1;
    rval_release( val->vec->vls + val->vec->len );
    return RERR_OK;
}

rval * rvec_peek ( rval * val, size_t index ) {
    if ( !val || !IS_VEC( val ) )
        return NULL;
    if ( index >= val->vec->len )
        return NULL;
    return val->vec->vls + index;
}

rerr rvec_set ( rval * val, size_t index, rval * item ) {
    ASSERT_VEC( val );
    if ( index >= val->vec->len )
        return RERR_USE_OOB;
    ASSERT_NOT_NULL( item );
    ASSERT_OK( rval_exclude( val ) );
    if ( rval_cyclesto( val, item ) )
        ASSERT_OK( rval_clone( val, val ) );
    rval tmp = rnil();
    ASSERT_OK( rval_copy( &tmp, item ) );
    rval_release( val->vec->vls + index );
    rval_move( val->vec->vls + index, &tmp );
    return RERR_OK;
}

rerr rvec_get ( rval * dst, size_t index, rval * val ) {
    ASSERT_NOT_NULL( dst );
    ASSERT_VEC( val );
    if ( index >= val->vec->len )
        return RERR_USE_OOB;
    return rval_copy( dst, val->vec->vls + index );
}

rerr rvec_fill ( rval * val, rval * item, size_t n ) {
    ASSERT_VEC( val );
    ASSERT_NOT_NULL( item );
    ASSERT_OK( rval_exclude( val ) );
    ASSERT_OK( rvec_reserve( val, rvec_len( val ) + n ) );
    if ( rval_cyclesto( val, item ) )
        ASSERT_OK( rval_clone( val, val ) );
    while ( val->vec->len < n )
        ASSERT_OK( rvec_push( val, item ) )
    return RERR_OK;
}

rerr rvec_reverse ( rval * val ) {
    ASSERT_VEC( val );
    ASSERT_OK( rval_exclude( val ) );
    rval tmp;
    rval * a, * b;
    for ( size_t i = 0; i < val->vec->len / 2; i++ ) {
        a = val->vec->vls + i;
        b = val->vec->vls + val->vec->len - 1 - i;
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
    return RERR_OK;
}

rerr rvec_concat ( rval * dst, rval * src ) {
    ASSERT_VEC( dst );
    ASSERT_VEC( src );
    ASSERT_OK( rval_exclude( dst ) );
    ASSERT_OK( rvec_reserve( dst, rvec_len( dst ) + rvec_len( src ) ) );
    rvec * a = dst->vec;
    rvec * b = src->vec;
    if ( !src->vec->len )
        return RERR_OK;
    memcpy( a->vls + a->len, b->vls, sizeof( rval ) * b->len );
    for ( size_t i = 0; i < b->len; i++ )
        rval_lease( a->vls + a->len + i );
    a->len += b->len;
    return RERR_OK;
}

rerr rvec_clear ( rval * val ) {
    ASSERT_VEC( val );
    ASSERT_OK( rval_exclude( val ) );
    for ( size_t i = 0; i < val->vec->len; i++ )
        rval_release( val->vec->vls + i );
    val->vec->len = 0;
    return RERR_OK;
}

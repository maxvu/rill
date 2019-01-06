#include "rval.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

int rval_type ( RVal * val ) {
    if ( !val )
        return 0;
    return val->typ;
}

int rval_lease ( RVal * val ) {
    if ( !val )
        return 0;
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX: break;
        case RVT_BUF: val->buf->ref++; break;
        case RVT_VEC: val->vec->ref++; break;
        case RVT_MAP: val->map->ref++; break;
    }
    return 1;
}

int rval_release ( RVal * val ) {
    if ( !val )
        return 0;
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX: break;
        case RVT_BUF: rbuf_release( val ); break;
        case RVT_VEC: rvec_release( val ); break;
        case RVT_MAP: rmap_release( val ); break;
    }
    *val = rnil();
    return 1;
}

int rval_exclude ( RVal * val ) {
    if ( !val )
        return 0;
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX: return 1; break;
        case RVT_BUF: return rbuf_exclude( val ); break;
        case RVT_VEC: return rvec_exclude( val ); break;
        case RVT_MAP: return rmap_exclude( val ); break;
        default: return 0;
    }
}

int rval_copy ( RVal * dst, RVal * src ) {
    if ( !dst )
        return 0;
    if ( !src )
        return 0;
    switch ( rval_type( src ) ) {
        case RVT_NIL:
            rval_release( dst );
            *dst = rnil();
            break;
        case RVT_IXX:
            rval_release( dst );
            *dst = rixx( src->ixx );
            break;
        case RVT_UXX:
            rval_release( dst );
            *dst = ruxx( src->uxx );
            break;
        case RVT_FXX:
            rval_release( dst );
            *dst = rfxx( src->fxx );
            break;
        case RVT_BUF:
            rval_release( dst );
            *dst = ( RVal ) { .typ = RVT_BUF, .buf = src->buf };
            dst->buf->ref++;
            break;
        case RVT_VEC:
            rval_release( dst );
            *dst = ( RVal ) { .typ = RVT_VEC, .vec = src->vec };
            dst->vec->ref++;
            break;
        case RVT_MAP:
            rval_release( dst );
            *dst = ( RVal ) { .typ = RVT_MAP, .map = src->map };
            dst->map->ref++;
            break;
        default:
            return 0;
            break;
    }
    return 1;
}

int rval_clone ( RVal * dst, RVal * src ) {
    if ( !dst )
        return 0;
    if ( !src )
        return 0;
    switch ( rval_type( src ) ) {
        case RVT_NIL:
            rval_release( dst );
            *dst = rnil();
            return 1;
            break;
        case RVT_IXX:
            rval_release( dst );
            *dst = rixx( src->ixx );
            return 1;
            break;
        case RVT_UXX:
            rval_release( dst );
            *dst = rixx( src->uxx );
            return 1;
            break;
        case RVT_FXX:
            rval_release( dst );
            *dst = rixx( src->uxx );
            return 1;
            break;
        case RVT_BUF: {
            RVal tmp = rnil();
            if ( !rbuf_init( &tmp, rbuf_len( src ) ) )
                return 0;
            if ( !rbuf_cpy( &tmp, src ) )
                return 0;
            rval_release( dst );
            *dst = tmp;
            return 1;
        } break;
        case RVT_VEC:
            return rvec_clone( dst, src );
            break;
        case RVT_MAP:
            return rmap_clone( dst, src );
            break;
        default:
            return 0;
            break;
    }
}

int rval_move ( RVal * dst, RVal * src ) {
    if ( !dst )
        return 0;
    if ( !src )
        return 0;
    rval_copy( dst, src );
    rval_release( src );
    return 1;
}

int rval_swap ( RVal * a, RVal * b ) {
    if ( !a )
        return 0;
    if ( !b )
        return 0;
    RVal tmp = rnil();
    rval_move( &tmp, a );
    rval_move( a, b );
    rval_move( b, &tmp );
    return 1;
}

int rval_eq ( RVal * a, RVal * b ) {
    if ( !a )
        return 0;
    if ( !b )
        return 0;
    if ( rval_type( a ) != rval_type( b ) )
        return 0;
    switch ( rval_type( a ) ) {
        case RVT_NIL: return 1; break;
        case RVT_IXX: return a->ixx == b->ixx; break;
        case RVT_UXX: return a->uxx == b->uxx; break;
        case RVT_FXX: return a->fxx == b->fxx; break;
        case RVT_BUF: return rbuf_cmp( a, b ) == 0; break;
        case RVT_VEC: {
            if ( rvec_len( a ) != rvec_len( b ) )
                return 0;
            for ( size_t i = 0; i < rvec_len( a ); i++ )
                if ( !rval_eq( rvec_get( a, i ), rvec_get( b, i ) ) )
                    return 0;
            return 1;
        } break;
        case RVT_MAP: {
            if ( rmap_size( a ) != rmap_size( b ) )
                return 0;
            RMapIter it = rmap_begin( a );
            while ( it ) {
                RVal * a_val = rmap_iter_val( it );
                RVal * b_val = rmap_get( b, rmap_iter_key( it ) );
                if ( !rval_eq( a_val, b_val ) )
                    return 0;
                it = rmap_iter_next( a, it );
            }
            return 1;
        } break;
        default: return 0; break;
    }
}

int rval_truthy ( RVal * val ) {
    if ( !val )
        return 0;
    switch ( rval_type( val ) ) {
        case RVT_NIL: return 0; break;
        case RVT_IXX: return val->ixx != 0; break;
        case RVT_UXX: return val->uxx == 0; break;
        case RVT_FXX: return val->fxx != 0.0 && !isnan( val->fxx ); break;
        case RVT_BUF: return rbuf_len( val ) != 0; break;
        case RVT_VEC: return rvec_len( val ) != 0; break;
        case RVT_MAP: return rmap_size( val ) != 0; break;
        default: return 0; break;
    }
}

int rval_isnil ( RVal * val ) {
    if ( !val )
        return 0;
    return val->typ == RVT_NIL;
}

int rval_cyclesto ( RVal * haystack, RVal * needle ) {
    if ( !haystack )
        return 0;
    if ( !needle )
        return 0;
    switch ( rval_type( haystack ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX:
        case RVT_BUF: return 0; break;
        case RVT_VEC: {
            if ( rval_type( needle ) == RVT_VEC )
                if ( haystack->vec == needle->vec )
                    return 1;
            for ( size_t i = 0; i < rvec_len( haystack ); i++ ) {
                if ( rval_cyclesto( rvec_get( haystack, i ), needle ) )
                    return 1;
            }
            return 0;
        } break;
        case RVT_MAP: {
            if ( rval_type( needle ) == RVT_MAP )
                if ( haystack->map == needle->map )
                    return 1;
            RMapIter it = rmap_begin( haystack );
            while ( it ) {
                if ( rval_cyclesto( rmap_iter_val( it ), needle ) )
                    return 1;
                it = rmap_iter_next( haystack, it );
            }
            return 0;
        } break;
        default: return 0; break;
    }
}

RVal rnil () {
    return ( RVal ) { .typ = RVT_NIL, .uxx = 0 };
}

RVal rixx ( RILL_IXX_TYPE i ) {
    return ( RVal ) { .typ = RVT_IXX, .ixx = i };
}

void rixx_set ( RVal * val, RILL_IXX_TYPE i ) {
    if ( !val ) return;
    *val = ( RVal ) { .typ = RVT_IXX, .ixx = i };
}

RILL_IXX_TYPE rixx_get ( RVal * val ) {
    if ( !val || rval_type( val ) != RVT_IXX )
        return 0;
    return val->ixx;
}

RVal ruxx ( RILL_UXX_TYPE u ) {
    return ( RVal ) {
        .typ = RVT_UXX,
        .uxx = u
    };
}

void ruxx_set ( RVal * val, RILL_UXX_TYPE u ) {
    if ( !val ) return;
    *val = ( RVal ) {
        .typ = RVT_UXX,
        .uxx = u
    };
}

RILL_UXX_TYPE ruxx_get ( RVal * val ) {
    if ( !val || rval_type( val ) != RVT_UXX )
        return 0;
    return val->uxx;
}

RVal rfxx ( RILL_FXX_TYPE f ) {
    return ( RVal ) {
        .typ = RVT_FXX,
        .fxx = f
    };
}

void rfxx_set ( RVal * val, RILL_FXX_TYPE f ) {
    if ( !val ) return;
    *val = ( RVal ) {
        .typ = RVT_FXX,
        .fxx = f
    };
}

RILL_FXX_TYPE rfxx_get ( RVal * val ) {
    if ( !val || rval_type( val ) != RVT_FXX )
        return 0;
    return val->fxx;
}

int rfxx_isfinite ( RVal * val ) {
    if ( !val || rval_type( val ) != RVT_FXX )
        return 0;
    return isfinite( val->fxx );
}

int rfxx_isinf ( RVal * val ) {
    if ( !val || rval_type( val ) != RVT_FXX )
        return 0;
    return isinf( val->fxx );
}

RVal rbuf () {
    RVal tmp = rnil();
    rbuf_init( &tmp, RILL_RBUF_DEFSIZ );
    return tmp;
}

int rbuf_realloc( RVal * bufval, size_t cap ) {
    RVal tmp = rnil();
    if ( !rbuf_init( &tmp, cap ) )
        return 0;
    if ( !rbuf_cpy( &tmp, bufval ) ) {
        rval_release( &tmp );
        return 0;
    }
    rval_release( bufval );
    *bufval = ( RVal ){
        .typ = RVT_BUF,
        .buf = tmp.buf
    };
    return 1;
}

int rbuf_init ( RVal * val, size_t cap ) {
    if ( !val )
        return 0;
    if ( cap < RILL_RBUF_MINSIZ )
        cap = RILL_RBUF_MINSIZ;
    RBuf * buf = RILL_ALLOC( sizeof( RBuf ) + sizeof( uint8_t ) * cap + 1 );
    if ( !buf )
        return 0;
    *buf = ( RBuf ) {
        .len = 0,
        .cap = cap,
        .ref = 1
    };
    memset( buf->bts, 0, sizeof( uint8_t ) * cap + 1 );
    rval_release( val );
    *val = ( RVal ) {
        .typ = RVT_BUF,
        .buf = buf,
    };
    return 1;
}

size_t rbuf_len ( RVal * bufval ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    return bufval->buf->len;
}

int rbuf_reserve ( RVal * bufval, size_t cap ) {
    if ( !bufval ) return 0;
    if ( rval_type( bufval ) != RVT_BUF )
        return 0;
    if ( bufval->buf->cap >= cap )
        return 1;
    return rbuf_realloc( bufval, cap );
}

int rbuf_exclude ( RVal * bufval ) {
    return rbuf_realloc( bufval, bufval->buf->cap );
}

int rbuf_compact ( RVal * bufval ) {
    if ( !bufval )
        return 0;
    if ( rval_type( bufval ) != RVT_BUF )
        return 0;
    size_t target = bufval->buf->len;
    if ( target < RILL_RBUF_MINSIZ )
        target = RILL_RBUF_MINSIZ;
    if ( bufval->buf->cap == target )
        return 1;
    return rbuf_realloc( bufval, target );
}

int rbuf_release ( RVal * bufval ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    RBuf * buf = bufval->buf;
    if ( --buf->ref )
        return 1;
    RILL_DEALLOC( buf );
    *bufval = rnil();
    return 1;
}

int rbuf_memcpy ( RVal * bufval, uint8_t * mem, size_t mem_len ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    if ( !mem )
        return 0;
    if ( !mem_len ) {
        rbuf_clear( bufval );
        return 1;
    }
    if ( !rbuf_reserve( bufval, mem_len ) )
        return 0;
    if ( !rbuf_exclude( bufval ) )
        return 0;
    RBuf * buf = bufval->buf;
    memcpy( buf->bts, mem, mem_len );
    buf->len = mem_len;
    buf->bts[ buf->len ] = 0;
    return 1;
}

int rbuf_memcat ( RVal * bufval, uint8_t * mem, size_t mem_len ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    if ( !mem )
        return 0;
    if ( !mem_len )
        return 1;
    if ( !rbuf_reserve( bufval, rbuf_len( bufval ) + mem_len ) )
        return 0;
    if ( !rbuf_exclude( bufval ) )
        return 0;
    RBuf * buf = bufval->buf;
    memcpy( buf->bts + buf->len, mem, mem_len );
    buf->len += mem_len;
    buf->bts[ buf->len ] = 0;
    return 1;
}

int rbuf_memcmp ( RVal * bufval, uint8_t * mem, size_t mem_len ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    if ( !mem )
        return 0;
    size_t max = bufval->buf->len > mem_len
        ? bufval->buf->len
        : mem_len;
    return memcmp( bufval->buf->bts, mem, max );
}

int rbuf_cpy ( RVal * dst, RVal * src ) {
    if ( !dst || rval_type( dst ) != RVT_BUF )
        return 0;
    if ( !src || rval_type( src ) != RVT_BUF )
        return 0;
    return rbuf_memcpy( dst, src->buf->bts, src->buf->len );
}

int rbuf_cat ( RVal * dst, RVal * src ) {
    if ( !dst || rval_type( dst ) != RVT_BUF )
        return 0;
    if ( !src || rval_type( src ) != RVT_BUF )
        return 0;
    return rbuf_memcat( dst, src->buf->bts, src->buf->len );
}

int rbuf_cmp ( RVal * a, RVal * b ) {
    if ( !a || rval_type( a ) != RVT_BUF )
        return 0;
    if ( !b || rval_type( b ) != RVT_BUF )
        return -19;
    size_t max = a->buf->len > b->buf->len
        ? a->buf->len
        : b->buf->len;
    return rbuf_memcmp( a, b->buf->bts, max );
}

int rbuf_strcpy ( RVal * bufval, const char * cstr ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    if ( !cstr )
        return 0;
    size_t cstr_len = strlen( cstr );
    return rbuf_memcpy( bufval, ( uint8_t * ) cstr, cstr_len );
}

int rbuf_strcat ( RVal * bufval, const char * cstr ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    if ( !cstr )
        return 0;
    size_t cstr_len = strlen( cstr );
    return rbuf_memcat( bufval, ( uint8_t * ) cstr, cstr_len );
}

int rbuf_strcmp ( RVal * bufval, const char * cstr ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    if ( !cstr )
        return 0;
    size_t cstr_len = strlen( cstr );
    return rbuf_memcmp( bufval, ( uint8_t * ) cstr, cstr_len );
}

int rbuf_clear ( RVal * bufval ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    bufval->buf->bts[ 0 ] = 0;
    bufval->buf->len = 0;
    return 1;
}

RVal rvec () {
    RVal tmp = rnil();
    rvec_init( &tmp, RILL_RVEC_DEFSIZ );
    return tmp;
}

int rvec_realloc ( RVal * vecval, size_t new_cap ) {
    RVal tmp = rnil();
    if ( !rvec_init( &tmp, new_cap ) )
        return 0;
    memcpy( tmp.vec->vls, vecval->vec->vls, sizeof( RVal ) * vecval->vec->len );
    RILL_DEALLOC( vecval->vec );
    vecval->vec = tmp.vec;
    return 1;
}

int rvec_init ( RVal * val, size_t cap ) {
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
    RVec * vec = RILL_ALLOC( sizeof( RVec ) + sizeof( RVal ) * cap );
    if ( !vec )
        return 0;
    *vec = ( RVec ) {
        .len = 0,
        .cap = cap,
        .ref = 1
    };
    rval_release( val );
    *val = ( RVal ) {
        .typ = RVT_VEC,
        .vec = vec
    };
    return 1;
}

size_t rvec_len ( RVal * vecval ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    return vecval->vec->len;
}

int rvec_reserve ( RVal * vecval, size_t cap ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    RVec * vec = vecval->vec;
    if ( vec->cap >= cap )
        return 1;
    return rvec_realloc( vecval, cap );
}

int rvec_compact ( RVal * vecval ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    RVec * vec = vecval->vec;
    size_t target = vec->len;
    if ( target < RILL_RVEC_MINSIZ )
        target = RILL_RVEC_MINSIZ;
    if ( target == vec->cap )
        return 1;
    return rvec_realloc( vecval, target );
}

int rvec_clone ( RVal * dst, RVal * src ) {
    if ( !dst )
        return 0;
    if ( !src || rval_type( src ) != RVT_VEC )
        return 0;
    RVal tmp = rnil();
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

int rvec_exclude ( RVal * vecval ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    return rvec_realloc( vecval, rvec_len( vecval ) );
}

int rvec_release ( RVal * vecval ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    RVec * vec = vecval->vec;
    if ( --vec->ref )
        return 1;
    for ( size_t i = 0; i < vec->len; i++ )
        rval_release( vec->vls + i );
    RILL_DEALLOC( vec );
    *vecval = rnil();
    return 1;
}

int rvec_push ( RVal * vecval, RVal * item ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    if ( !item )
        return 0;
    RVec * vec = vecval->vec;
    if ( vec->len == vec->cap )
        if ( !rvec_reserve( vecval, RILL_RVEC_GROWTH * vec->cap ) )
            return 0;
    if ( vec->ref > 1 || rval_cyclesto( item, vecval ) )
        if ( !rval_exclude( vecval ) )
            return 0;
    vec = vecval->vec;
    rval_copy( vec->vls + vec->len, item );
    vec->len++;
    return 1;
}

int rvec_pop ( RVal * vecval ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    if ( !rvec_len( vecval ) )
        return 0;
    RVec * vec = vecval->vec;
    if ( vec->ref > 1 && !rval_exclude( vecval ) )
        return 0;
    vec = vecval->vec;
    rval_release( vec->vls + vec->len - 1 );
    vec->len--;
    return 1;
}

RVal * rvec_get ( RVal * vecval, size_t idx ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return NULL;
    RVec * vec = vecval->vec;
    if ( idx >= vec->len )
        return NULL;
    return vec->vls + idx;
}

int rvec_set ( RVal * vecval, size_t idx, RVal * item ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    if ( !item )
        return 0;
    RVec * vec = vecval->vec;
    if ( idx >= vec->len )
        return 0;
    if ( vec->ref > 1 || rval_cyclesto( item, vecval ) )
        if ( !rval_exclude( vecval ) )
            return 0;
    vec = vecval->vec;
    rval_copy( vec->vls + idx, item );
    return 1;
}

int rvec_fill ( RVal * vecval, RVal * item, size_t n ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    RVec * vec = vecval->vec;
    if ( vec->cap < n )
        if ( !rvec_reserve( vecval, RILL_RVEC_GROWTH * vec->cap ) )
            return 0;
    if ( vec->ref > 1 || rval_cyclesto( item, vecval ) )
        if ( !rval_exclude( vecval ) )
            return 0;
    vec = vecval->vec;
    for ( size_t i = 0; i < n; i++ )
        rval_copy( vec->vls + i, item );
    vec->len = n;
    return 1;
}

int rvec_reverse ( RVal * vecval ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    RVec * vec = vecval->vec;
    if ( vec->ref > 1 && !rval_exclude( vecval ) )
        return 0;
    vec = vecval->vec;
    for ( size_t i = 0; i < vec->len / 2; i++ )
        rval_swap( vec->vls + i, vec->vls + ( vec->len - 1 - i ) );
    return 1;
}

int rvec_concat ( RVal * dstval, RVal * srcval ) {
    if ( !dstval || rval_type( dstval ) != RVT_VEC )
        return 0;
    if ( !srcval || rval_type( srcval ) != RVT_VEC )
        return 0;
    RVal tmp = rnil();
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

int rvec_clear ( RVal * vecval ) {
    if ( !vecval || rval_type( vecval ) != RVT_VEC )
        return 0;
    RVec * vec = vecval->vec;
    if ( vec->ref > 1 && !rval_exclude( vecval ) )
        return 0;
    vec = vecval->vec;
    for ( size_t i = 0; i < vec->len; i++ )
        rval_release( vec->vls + i );
    vec->len = 0;
    return 1;
}

RVal rmap () {
    RVal tmp = rnil();
    rmap_init( &tmp, RILL_RMAP_DEFSIZ );
    return tmp;
}

RMapSlot * rmap_hash_a ( RMap * map, RBuf * keybuf ) {
    size_t hash = 0; // sdbm
    uint8_t * key = keybuf->bts;
    size_t len = keybuf->len;
    for ( size_t i = 0; i < len; i++ )
        hash = key[ i ] + ( hash << 6 ) + ( hash << 16 ) - hash;
    size_t idx = ( hash % ( map->cap / 4 ) ) + ( map->cap / 4 ) * 0;
    return map->slt + idx;
}

RMapSlot * rmap_hash_b ( RMap * map, RBuf * keybuf ) {
    size_t hash = 5381; // djb
    uint8_t * key = keybuf->bts;
    size_t len = keybuf->len;
    for ( size_t i = 0; i < len; i++ )
        hash = ( hash << 5 ) + hash + key[ i ];
    size_t idx = ( hash % ( map->cap / 4 ) ) + ( map->cap / 4 ) * 1;
    return map->slt + idx;
}

RMapSlot * rmap_hash_c ( RMap * map, RBuf * keybuf ) {
    size_t hash = 56923; // hand-rolled
    uint8_t * key = keybuf->bts;
    size_t len = keybuf->len;
    for ( size_t i = 0; i < len; i++ )
        hash = ( hash << 7 ) ^ ( hash - key[ i ] );
    size_t idx = ( hash % ( map->cap / 4 ) ) + ( map->cap / 4 ) * 2;
    return map->slt + idx;
}

RMapSlot * rmap_hash_d ( RMap * map, RBuf * keybuf ) {
    size_t hash = 77317; // one-at-a-time
    uint8_t * key = keybuf->bts;
    size_t len = keybuf->len;
    for ( size_t i = 0; i < len; i++ )
        hash = ( ( hash << 10 ) ^ ( hash >> 6 ) ) + key[ i ];
    size_t idx = ( hash % ( map->cap / 4 ) ) + ( map->cap / 4 ) * 3;
    return map->slt + idx;
}

void rmapslot_swap ( RMapSlot * a, RMapSlot * b ) {
    RMapSlot tmp = *a;
    *a = *b;
    *b = tmp;
}

int rmap_realloc ( RVal * mapval, size_t new_cap ) {
    RVal tmp = rnil();
    if ( !rmap_init( &tmp, new_cap ) )
        return 0;
    RMapIter it = rmap_begin( mapval );
    while ( it ) {
        if ( !rmap_set( &tmp, rmap_iter_key( it ), rmap_iter_val( it ) ) ) {
            rval_release( &tmp );
            return 0;
        }
        it = rmap_iter_next( mapval, it );
    }
    rmap_release( mapval );
    return 1;
}

int rmap_init ( RVal * mapval, size_t cap ) {
    if ( !mapval )
        return 0;
    if ( rval_type( mapval ) == RVT_MAP ) {
        if ( !rmap_reserve( mapval, cap ) )
            return 0;
        rmap_clear( mapval );
        return 1;
    }
    if ( cap < RILL_RMAP_MINSIZ )
        cap = RILL_RMAP_MINSIZ;
    cap += 4 - ( cap % 4 );
    RMap * map = RILL_ALLOC( sizeof( RMap ) + sizeof( RMapSlot ) * cap );
    if ( !map )
        return 0;
    *map = ( RMap ) {
        .occ = 0,
        .cap = cap,
        .ref = 1
    };
    for ( size_t i = 0; i < cap; i++ ) {
        *( map->slt + i ) = ( RMapSlot ) {
            .key = rnil(),
            .val = rnil()
        };
    }
    rmap_release( mapval );
    *mapval = ( RVal ) {
        .typ = RVT_MAP,
        .map = map
    };
    return 1;
}

size_t rmap_size ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    return mapval->map->occ;
}

int rmap_reserve ( RVal * mapval, size_t cap ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( mapval->map->cap >= cap )
        return 1;
    return rmap_realloc( mapval, cap );
}

int rmap_compact ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    RMap * map = mapval->map;
    size_t target = map->occ;
    if ( target < RILL_RMAP_MINSIZ )
        target = RILL_RMAP_MINSIZ;
    if ( target == map->cap )
        return 1;
    return rmap_realloc( mapval, target );
}

int rmap_clone ( RVal * dst, RVal * src_mapval ) {
    if ( !src_mapval || rval_type( src_mapval ) != RVT_MAP )
        return 0;
    if ( !dst )
        return 0;
    RVal tmp = rnil();
    if ( !rmap_init( &tmp, rmap_size( src_mapval ) ) )
        return 0;
    RMapIter it = rmap_begin( src_mapval );
    while ( it ) {
        // TODO: call rval_clone() here
        if ( !rmap_set( &tmp, rmap_iter_key( it ), rmap_iter_val( it ) ) ) {
            rmap_release( &tmp );
            return 0;
        }

        it = rmap_iter_next( src_mapval, it );
    }
    rval_move( dst, &tmp );
    return 1;
}

int rmap_exclude ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    return rmap_realloc( mapval, mapval->map->occ );
}

int rmap_release ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    RMap * map = mapval->map;
    if ( --map->ref )
        return 1;
    RMapIter it = rmap_begin( mapval );
    while ( it ) {
        rval_release( &it->key );
        rval_release( &it->val );
        it = rmap_iter_next( mapval, it );
    }
    RILL_DEALLOC( map );
    *mapval = rnil();
    return 1;
}

int rmap_set ( RVal * mapval, RVal * keyval, RVal * item ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( !keyval || rval_type( keyval ) != RVT_BUF )
        return 0;

    // resize preemptively
    RMap * map = mapval->map;
    double new_load = ( ( double ) map->occ + 1 ) / ( double ) map->cap;
    if ( new_load > RILL_RMAP_MAXLOD )
        if ( !rmap_reserve( mapval, map->occ * RILL_RMAP_GROWTH ) )
            return 0;
    map = mapval->map;

    // break cycles
    if ( rval_cyclesto( item, mapval ) && !rval_exclude( mapval ) )
        return 0;
    map = mapval->map;

    // exclude
    if ( map->ref > 1 && !rval_exclude( mapval ) )
        return 0;
    map = mapval->map;

    RMapSlot juggle = ( RMapSlot ) {
        .key = *keyval,
        .val = *item
    };

    rmapslot_swap( &juggle, rmap_hash_a( map, keyval->buf ) );

    while ( 1 ) {

        if ( rval_isnil( &juggle.key ) || rbuf_cmp( &juggle.key, keyval ) == 0 )
            break;
        rmapslot_swap( &juggle, rmap_hash_b( map, juggle.key.buf ) );

        if ( rval_isnil( &juggle.key ) || rbuf_cmp( &juggle.key, keyval ) == 0 )
            break;
        rmapslot_swap( &juggle, rmap_hash_c( map, juggle.key.buf ) );

        if ( rval_isnil( &juggle.key ) || rbuf_cmp( &juggle.key, keyval ) == 0 )
            break;
        rmapslot_swap( &juggle, rmap_hash_d( map, juggle.key.buf ) );

        if ( rval_isnil( &juggle.key ) || rbuf_cmp( &juggle.key, keyval ) == 0 )
            break;
        rmapslot_swap( &juggle, rmap_hash_a( map, juggle.key.buf ) );

    }

    if ( rval_isnil( &juggle.key ) ) {
        rval_lease( keyval );
        rval_lease( item );
        map->occ++;
        return 1;
    } else {
        if ( !rmap_reserve( mapval, map->cap * RILL_RMAP_GROWTH ) )
            return 0;
        return rmap_set( mapval, keyval, item );
    }
}

RVal * rmap_get ( RVal * mapval, RVal * keyval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return NULL;
    if ( !keyval || rval_type( keyval ) != RVT_BUF )
        return NULL;
    RMap * map = mapval->map;
    RBuf * key = keyval->buf;
    RMapSlot * hit;

    if ( ( hit = rmap_hash_a( map, key ) ) && !rval_isnil( &hit->key ) )
        return &hit->val;
    if ( ( hit = rmap_hash_b( map, key ) ) && !rval_isnil( &hit->key ) )
        return &hit->val;
    if ( ( hit = rmap_hash_c( map, key ) ) && !rval_isnil( &hit->key ) )
        return &hit->val;
    if ( ( hit = rmap_hash_d( map, key ) ) && !rval_isnil( &hit->key ) )
        return &hit->val;
    return NULL;
}

int rmap_unset ( RVal * mapval, RVal * keyval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( !keyval || rval_type( keyval ) != RVT_BUF )
        return 0;
    RMap * map = mapval->map;
    RBuf * key = keyval->buf;
    RMapSlot * hit;

    if ( ( hit = rmap_hash_a( map, key ) ) && !rval_isnil( &hit->key ) ) {
        rval_release( &hit->key );
        rval_release( &hit->val );
        map->occ--;
        return 1;
    }
    if ( ( hit = rmap_hash_b( map, key ) ) && !rval_isnil( &hit->key ) ) {
        rval_release( &hit->key );
        rval_release( &hit->val );
        map->occ--;
        return 1;
    }
    if ( ( hit = rmap_hash_c( map, key ) ) && !rval_isnil( &hit->key ) ) {
        rval_release( &hit->key );
        rval_release( &hit->val );
        map->occ--;
        return 1;
    }
    if ( ( hit = rmap_hash_d( map, key ) ) && !rval_isnil( &hit->key ) ) {
        rval_release( &hit->key );
        rval_release( &hit->val );
        map->occ--;
        return 1;
    }
    return 0;
}

int rmap_keys ( RVal * dstval, RVal * src_mapval ) {
    if ( !src_mapval || rval_type( src_mapval ) != RVT_MAP )
        return 0;
    if ( !dstval )
        return 0;
    RVal tmp = rnil();
    if ( !rvec_init( &tmp, rmap_size( src_mapval ) ) )
        return 0;
    RMapIter it = rmap_begin( src_mapval );
    while ( it ) {
        if ( !rvec_push( &tmp, rmap_iter_key( it ) ) ) {
            rvec_release( &tmp );
            return 0;
        }
        it = rmap_iter_next( src_mapval, it );
    }
    rval_move( dstval, &tmp );
    return 1;
}

int rmap_vals ( RVal * dstval, RVal * src_mapval ) {
    if ( !src_mapval || rval_type( src_mapval ) != RVT_MAP )
        return 0;
    if ( !dstval )
        return 0;
    RVal tmp = rnil();
    if ( !rvec_init( &tmp, rmap_size( src_mapval ) ) )
        return 0;
    RMapIter it = rmap_begin( src_mapval );
    while ( it ) {
        if ( !rvec_push( &tmp, rmap_iter_val( it ) ) ) {
            rvec_release( &tmp );
            return 0;
        }
        it = rmap_iter_next( src_mapval, it );
    }
    rval_move( dstval, &tmp );
    return 1;
}

int rmap_merge ( RVal * dstval, RVal * srcval ) {
    if ( !dstval || rval_type( dstval ) != RVT_MAP )
        return 0;
    if ( !srcval || rval_type( srcval ) != RVT_MAP )
        return 0;
    // TODO: can you safely rmap_merge without copying?
    RVal tmp = rnil();
    if ( !rmap_init( &tmp, rmap_size( srcval ) ) )
        return 0;
    RMapIter it = rmap_begin( srcval );
    while ( it ) {
        if ( !rmap_set( &tmp, rmap_iter_key( it ), rmap_iter_val( it ) ) ) {
            rval_release( &tmp );
            return 0;
        }
        it = rmap_iter_next( srcval, it );
    }
    rval_move( dstval, &tmp );
    return 1;
}

int rmap_clear ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    RMapIter it = rmap_begin( mapval );
    while ( it ) {
        rmap_iter_del( mapval, it );
        it = rmap_iter_next( mapval, it );
    }
    return 1;
}

RMapIter rmap_begin ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    RMap * map = mapval->map;
    RMapIter it = map->slt;
    if ( !rmap_iter_key( it ) )
        it = rmap_iter_next( mapval, it );
    return it;
}

RMapIter rmap_iter_next ( RVal * mapval, RMapIter it ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( !it )
        return NULL;
    RMap * map = mapval->map;
    while ( rval_type( &it->key ) != RVT_BUF && it < map->slt + map->cap )
        it++;
    if ( it == map->slt + map->cap )
        it = NULL;
    return it;
}

RVal * rmap_iter_key ( RMapIter it ) {
    if ( !it )
        return NULL;
    return &it->key;
}

RVal * rmap_iter_val ( RMapIter it ) {
    if ( !it )
        return NULL;
    return &it->val;
}

RMapIter rmap_iter_del ( RVal * mapval, RMapIter it ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( !it )
        return NULL;
    rval_release( &it->key );
    rval_release( &it->val );
    mapval->map->occ--;
    return rmap_iter_next( mapval, it );
}

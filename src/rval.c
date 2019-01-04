#include "rval.h"

#include <stdlib.h>
#include <string.h>

int rval_type ( RVal * val ) {
    if ( !val ) return 0;
    return val->typ;
}

int rval_lease ( RVal * val ) {
    if ( !val ) return 0;
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

// int rval_release ( RVal * val ) {
//
// }
//
// int rval_exclude ( RVal * val );
//
// int rval_copy ( RVal * dst, RVal * src ) {
//
// }
//
// int rval_clone ( RVal * dst, RVal * src ) {
//
// }
//
// int rval_move ( RVal * dst, RVal * src ) {
//
// }
//
// int rval_swap ( RVal * a, RVal * b ) {
//
// }
//
// int rval_eq ( RVal * a, RVal * b ) {
//
// }

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
    if ( !rval_exclude( bufval ) )
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
    if ( !rval_exclude( bufval ) )
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

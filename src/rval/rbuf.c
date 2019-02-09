#include "config/alloc.h"
#include "rval/rbuf.h"
#include "rval/rval.h"

#include <string.h>

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

uint8_t * rbuf_get ( RVal * bufval ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    return bufval->buf->bts;
}

char * rbuf_strget ( RVal * bufval ) {
    if ( !bufval || rval_type( bufval ) != RVT_BUF )
        return 0;
    return ( char * ) bufval->buf->bts;
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
    rbuf_clear( bufval );
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

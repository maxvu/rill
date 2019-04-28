#include "config/alloc.h"
#include "config/rerr.h"
#include "rval/rbuf.h"
#include "rval/rval.h"

#include <string.h>

rval rbuf () {
    rval tmp = rnil();
    rbuf_init( &tmp, RILL_RBUF_DEFSIZ );
    return tmp;
}

int rbuf_realloc( rval * bufval, size_t cap ) {
    rval tmp = rnil();
    if ( !rbuf_init( &tmp, cap ) )
        return 0;
    if ( !rbuf_cpy( &tmp, bufval ) ) {
        rval_release( &tmp );
        return 0;
    }
    rval_release( bufval );
    *bufval = ( rval ){
        .typ = RVT_BUF,
        .buf = tmp.buf
    };
    return 1;
}

int rbuf_init ( rval * val, size_t cap ) {
    if ( !val ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }
    if ( cap < RILL_RBUF_MINSIZ )
        cap = RILL_RBUF_MINSIZ;
    RBuf * buf = RILL_ALLOC( sizeof( RBuf ) + sizeof( uint8_t ) * cap + 1 );
    if ( !buf ) {
        rerr_set( RILL_ERR_ALLOC );
        return 0;
    }
    *buf = ( RBuf ) {
        .len = 0,
        .cap = cap,
        .ref = 1
    };
    memset( buf->bts, 0, sizeof( uint8_t ) * cap + 1 );
    rval_release( val );
    *val = ( rval ) {
        .typ = RVT_BUF,
        .buf = buf,
    };
    return 1;
}

size_t rbuf_len ( rval * bufval ) {
    RILL_ASSERT_ISBUF( bufval );
    return bufval->buf->len;
}

uint8_t * rbuf_get ( rval * bufval ) {
    RILL_ASSERT_ISBUF( bufval );
    return bufval->buf->bts;
}

char * rbuf_strget ( rval * bufval ) {
    RILL_ASSERT_ISBUF( bufval );
    return ( char * ) bufval->buf->bts;
}

int rbuf_reserve ( rval * bufval, size_t cap ) {
    RILL_ASSERT_ISBUF( bufval );
    if ( bufval->buf->cap >= cap )
        return 1;
    return rbuf_realloc( bufval, cap );
}

int rbuf_exclude ( rval * bufval ) {
    RILL_ASSERT_ISBUF( bufval );
    return rbuf_realloc( bufval, bufval->buf->cap );
}

int rbuf_compact ( rval * bufval ) {
    RILL_ASSERT_ISBUF( bufval );
    size_t target = bufval->buf->len;
    if ( target < RILL_RBUF_MINSIZ )
        target = RILL_RBUF_MINSIZ;
    if ( bufval->buf->cap == target )
        return 1;
    return rbuf_realloc( bufval, target );
}

int rbuf_release ( rval * bufval ) {
    RILL_ASSERT_ISBUF( bufval );
    RBuf * buf = bufval->buf;
    if ( --buf->ref )
        return 1;
    rbuf_clear( bufval );
    RILL_DEALLOC( buf );
    *bufval = rnil();
    return 1;
}

int rbuf_memcpy ( rval * bufval, uint8_t * mem, size_t mem_len ) {
    RILL_ASSERT_ISBUF( bufval );
    RILL_ASSERT_ARGNOTNULL( mem );
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

int rbuf_memcat ( rval * bufval, uint8_t * mem, size_t mem_len ) {
    RILL_ASSERT_ISBUF( bufval );
    RILL_ASSERT_ARGNOTNULL( mem );
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

int rbuf_memcmp ( rval * bufval, uint8_t * mem, size_t mem_len ) {
    RILL_ASSERT_ISBUF( bufval );
    RILL_ASSERT_ARGNOTNULL( mem );
    size_t max = bufval->buf->len > mem_len
        ? bufval->buf->len
        : mem_len;
    return memcmp( bufval->buf->bts, mem, max );
}

int rbuf_cpy ( rval * dst, rval * src ) {
    RILL_ASSERT_ARGNOTNULL( dst );
    RILL_ASSERT_ISBUF( src );
    return rbuf_memcpy( dst, src->buf->bts, src->buf->len );
}

int rbuf_cat ( rval * dst, rval * src ) {
    RILL_ASSERT_ISBUF( dst );
    RILL_ASSERT_ISBUF( src );
    return rbuf_memcat( dst, src->buf->bts, src->buf->len );
}

int rbuf_cmp ( rval * a, rval * b ) {
    RILL_ASSERT_ISBUF( a );
    RILL_ASSERT_ISBUF( b );
    size_t max = a->buf->len > b->buf->len
        ? a->buf->len
        : b->buf->len;
    return rbuf_memcmp( a, b->buf->bts, max );
}

int rbuf_strcpy ( rval * bufval, const char * cstr ) {
    RILL_ASSERT_ARGNOTNULL( bufval );
    RILL_ASSERT_ARGNOTNULL( cstr );
    size_t cstr_len = strlen( cstr );
    return rbuf_memcpy( bufval, ( uint8_t * ) cstr, cstr_len );
}

int rbuf_strcat ( rval * bufval, const char * cstr ) {
    RILL_ASSERT_ISBUF( bufval );
    RILL_ASSERT_ARGNOTNULL( cstr );
    size_t cstr_len = strlen( cstr );
    return rbuf_memcat( bufval, ( uint8_t * ) cstr, cstr_len );
}

int rbuf_strcmp ( rval * bufval, const char * cstr ) {
    RILL_ASSERT_ISBUF( bufval );
    RILL_ASSERT_ARGNOTNULL( cstr );
    size_t cstr_len = strlen( cstr );
    return rbuf_memcmp( bufval, ( uint8_t * ) cstr, cstr_len );
}

int rbuf_clear ( rval * bufval ) {
    RILL_ASSERT_ISBUF( bufval );
    bufval->buf->bts[ 0 ] = 0;
    bufval->buf->len = 0;
    return 1;
}

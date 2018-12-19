#include "rval/rbuf.h"
#include "rval/rnil.h"

#include <stdlib.h>
#include <string.h>

int rbuf_resize ( RVal * bufval, size_t new_cap ) {
    RBuf * resized = ( RBuf * ) RILL_REALLOC(
        bufval->buf,
        sizeof( RBuf ) + sizeof( uint8_t ) * new_cap + 1
    );
    if ( !resized )
        return 0;
    resized->bytes[ resized->len ] = 0;
    resized->cap = new_cap;
    bufval->buf = resized;
    return 1;
}

RVal rbuf ( size_t init_cap ) {
    if ( init_cap < RILL_RBUF_MINCAP )
        init_cap = RILL_RBUF_MINCAP;
    RVal val = rnil();
    size_t target = sizeof( RBuf ) + sizeof( uint8_t ) * init_cap + 1;
    RBuf * buf = ( RBuf * ) RILL_ALLOC( target );
    if ( !buf )
        return val;
    memset( buf, 0, sizeof( RBuf ) + sizeof( uint8_t ) );
    buf->ref = 1;
    buf->cap = init_cap;
    rvinfo_settype( &val.info, RVT_BUF );
    return val;
}

size_t rbuf_len ( RVal * bufval ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return 0; }
    return bufval->buf->len;
}

int rbuf_reserve ( RVal * bufval, size_t new_cap ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return 0; }
    if ( bufval->buf->cap >= new_cap )
        return 1;
    return rbuf_resize( bufval, new_cap );
}

int rbuf_compact ( RVal * bufval ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return 0; }
    size_t target = bufval->buf->len;
    if ( target < RILL_RBUF_MINCAP )
        target = RILL_RBUF_MINCAP;
    if ( rbuf_len( bufval ) == target )
        return 1;
    return rbuf_resize( bufval, target );
}

uint8_t * rbuf_get ( RVal * bufval ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return NULL; }
    return bufval->buf->bytes;
}

int rbuf_cpy ( RVal * dst, RVal * src ) {
    RILL_RVAL_ENFORCETYPE( dst, RVT_BUF ) { return 0; }
    RILL_RVAL_ENFORCETYPE( src, RVT_BUF ) { return 0; }
    return rbuf_memcpy( dst, src->buf->bytes, src->buf->len );
}

int rbuf_cat ( RVal * dst, RVal * src ) {
    RILL_RVAL_ENFORCETYPE( dst, RVT_BUF ) { return 0; }
    RILL_RVAL_ENFORCETYPE( src, RVT_BUF ) { return 0; }
    return rbuf_memcat( dst, src->buf->bytes, src->buf->len );
}

int rbuf_cmp ( RVal * a, RVal * b ) {
    RILL_RVAL_ENFORCETYPE( a, RVT_BUF ) { return 0; }
    RILL_RVAL_ENFORCETYPE( b, RVT_BUF ) { return 0; }
    return rbuf_memcmp( a, b->buf->bytes, b->buf->len );
}

int rbuf_strcpy ( RVal * bufval, const char * cstr ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return 0; }
    size_t cstr_len = strlen( cstr );
    return rbuf_memcpy( bufval, ( uint8_t * ) cstr, cstr_len );
}

int rbuf_strcat ( RVal * bufval, const char * cstr ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return 0; }
    size_t cstr_len = strlen( cstr );
    return rbuf_memcat( bufval, ( uint8_t * ) cstr, cstr_len );
}

int rbuf_strcmp ( RVal * bufval, const char * cstr ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return 0; }
    size_t cstr_len = strlen( cstr );
    return rbuf_memcmp( bufval, ( uint8_t * ) cstr, cstr_len );
}

int rbuf_memcpy ( RVal * bufval, const uint8_t * mem, size_t mem_len ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return 0; }
    if ( !rbuf_reserve( bufval, mem_len ) )
        return 0;
    memcpy( bufval->buf->bytes, mem, mem_len );
    bufval->buf->len = mem_len;
    bufval->buf->bytes[ bufval->buf->len ] = 0;
    return 1;
}
int rbuf_memcat ( RVal * bufval, const uint8_t * mem, size_t mem_len ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return 0; }
    size_t target = ( double ) bufval->buf->len * RILL_RBUF_GROWTHFACT;
    if ( !rbuf_reserve( bufval, target ) )
        return 0;
    memcpy( bufval->buf->bytes + bufval->buf->len, mem, mem_len );
    bufval->buf->len += mem_len;
    bufval->buf->bytes[ bufval->buf->len ] = 0;
    return 1;
}
int rbuf_memcmp ( RVal * bufval, const uint8_t * mem, size_t mem_len ) {
    RILL_RVAL_ENFORCETYPE( bufval, RVT_BUF ) { return 0; }
    if ( mem_len > bufval->buf->len )
        return -1;
    if ( mem_len < bufval->buf->len )
        return 1;
    return memcmp( bufval->buf->bytes, mem, mem_len );
}

#include "config.h"
#include "val/rbuffer.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RBuffer * rbuffer_create ( size_t init_cap ) {
    if ( init_cap < RILL_VAL_RBUFFER_MINSIZE )
        init_cap = RILL_VAL_RBUFFER_MINSIZE;
    RBuffer * buf = RILL_ALLOC( sizeof( RBuffer ) );
    if ( !buf )
        return NULL;
    buf->bytes = RILL_ALLOC( sizeof( uint8_t ) * init_cap );
    if ( !buf->bytes ) {
        RILL_DEALLOC( buf );
        return NULL;
    }
    buf->bytes[ 0 ] = 0;
    buf->ref = 1;
    buf->len = 0;
    buf->cap = init_cap;
    return buf;
}

RBuffer * rbuffer_clone ( RBuffer * buf ) {
    assert( buf );
    RBuffer * clone = rbuffer_create( buf->len );
    if ( !clone )
        return NULL;
    if ( !rbuffer_cpy( clone, buf ) ) {
        rbuffer_destroy( clone );
        return NULL;
    }
    return clone;
}

void rbuffer_destroy ( RBuffer * buf ) {
    assert( buf );
    RILL_DEALLOC( buf->bytes );
    RILL_DEALLOC( buf );
}

size_t rbuffer_len ( RBuffer * buf ) {
    assert( buf );
    return buf->len;
}

size_t rbuffer_lease ( RBuffer * buf ) {
    assert( buf );
    return ++buf->ref;
}

size_t rbuffer_release ( RBuffer * buf ) {
    assert( buf );
    return --buf->ref;
}

int __rbuffer_resize ( RBuffer * buf, size_t new_cap ) {
    assert( buf );
    uint8_t * new_bytes;
    if ( !( new_bytes = RILL_REALLOC( buf->bytes, new_cap + 1 ) ) )
        return 0;
    buf->bytes = new_bytes;
    buf->cap = new_cap;
    return 1;
}

int rbuffer_reserve ( RBuffer * buf, size_t new_cap ) {
    assert( buf );
    if ( buf->cap >= new_cap )
        return 1;
    return __rbuffer_resize( buf, new_cap );
}

int rbuffer_compact ( RBuffer * buf ) {
    assert( buf );
    size_t target = buf->len;
    if ( target < RILL_VAL_RBUFFER_MINSIZE )
        target = RILL_VAL_RBUFFER_MINSIZE;
    if ( buf->cap == target )
        return 1;
    return __rbuffer_resize( buf, target );
}

uint8_t * rbuffer_get ( RBuffer * buf ) {
    assert( buf );
    return buf->bytes;
}

int __rbuffer_cat( RBuffer * dst, uint8_t * src, size_t src_len ) {
    assert( dst );
    assert( src );
    if ( !rbuffer_reserve( dst, dst->len + src_len ) )
        return 0;
    memcpy(
        dst->bytes + dst->len,
        src,
        sizeof( uint8_t ) * src_len
    );
    dst->len += src_len;
    dst->bytes[ dst->len ] = 0;
    return 1;
}

int rbuffer_cpy ( RBuffer * dst, RBuffer * src ) {
    assert( dst );
    assert( src );
    if ( !rbuffer_reserve( dst, dst->len + src->len ) )
        return 0;
    rbuffer_clear( dst );
    return __rbuffer_cat( dst, src->bytes, src->len );
}

int rbuffer_cat ( RBuffer * dst, RBuffer * src ) {
    assert( dst );
    assert( src );
    return __rbuffer_cat( dst, src->bytes, src->len );
}

int rbuffer_cmp ( RBuffer * a, RBuffer * b ) {
    assert( a );
    assert( b );
    // TODO: length comparison
    size_t min = a->len < b->len ? a->len : b->len;
    return memcmp( a, b, min );
}

int rbuffer_cpyc ( RBuffer * buf, char * cstr ) {
    assert( buf );
    assert( cstr );
    size_t cstr_len = strlen( cstr );
    if ( !rbuffer_reserve( buf, cstr_len ) )
        return 0;
    rbuffer_clear( buf );
    return __rbuffer_cat( buf, ( uint8_t * ) cstr, cstr_len );
}

int rbuffer_catc ( RBuffer * buf, char * cstr ) {
    assert( buf );
    assert( cstr );
    return __rbuffer_cat( buf, ( uint8_t * ) cstr, strlen( cstr ) );
}

int rbuffer_cmpc ( RBuffer * buf, char * cstr ) {
    assert( buf );
    assert( cstr );
    size_t cstr_len = strlen( cstr );
    size_t min = buf->len < cstr_len ? buf->len : cstr_len;
    return memcmp( buf->bytes, cstr, min );
}

int rbuffer_cpymem ( RBuffer * buf, uint8_t * bytes, size_t bytes_len ) {
    assert( buf );
    assert( bytes );
    if ( !rbuffer_reserve( buf, bytes_len ) )
        return 0;
    rbuffer_clear( buf );
    return __rbuffer_cat( buf, bytes, bytes_len );
}

int rbuffer_catmem ( RBuffer * buf, uint8_t * bytes, size_t bytes_len ) {
    assert( buf );
    assert( bytes );
    return __rbuffer_cat( buf, bytes, bytes_len );
}

int rbuffer_cmpmem ( RBuffer * buf, uint8_t * bytes, size_t bytes_len ) {
    assert( buf );
    size_t min = buf->len < bytes_len ? buf->len : bytes_len;
    return memcmp( buf, bytes, min );
}

void rbuffer_clear ( RBuffer * buf ) {
    assert( buf );
    buf->bytes[ 0 ] = 0;
    buf->len = 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "environment.h"
#include "rval/rbuf.h"

int __rbuf_resize ( RBuf * buf, size_t new_cap ) {
    TATTLE_IF( buf == NULL );
    TATTLE_IF( new_cap < buf->len );
    new_cap = sizeof( char ) * new_cap + 1;
    char * new_buffer = RILL_REALLOC( buf->buffer, new_cap );
    if ( new_buffer == NULL )
        return 0;
    buf->buffer = new_buffer;
    buf->cap = new_cap;
    return 1;
}

RBuf * rbuf_create ( size_t init_cap ) {
    RBuf * buf = RILL_ALLOC( sizeof( RBuf ) );
    if ( !buf )
        return NULL;
    if ( init_cap < RILL_RBUF_MINSIZE )
        init_cap = RILL_RBUF_MINSIZE;
    buf->buffer = RILL_ALLOC( sizeof( char ) * init_cap + 1 );
    if ( buf->buffer == NULL ) {
        RILL_DEALLOC( buf );
        return NULL;
    }
    buf->buffer[ 0 ] = 0;
    buf->len = 0;
    buf->cap = init_cap;
    buf->refcount = 1;
    return buf;
}

void rbuf_destroy ( RBuf * buf ) {
    TATTLE_IF( buf == NULL );
    TATTLE_IF( buf->buffer == NULL );
    free( buf->buffer );
    free( buf );
}

void rbuf_ref ( RBuf * buf ) {
    TATTLE_IF( buf == NULL );
    buf->refcount++;
}

void rbuf_deref ( RBuf * buf ) {
    TATTLE_IF( buf == NULL );
    if ( !--buf->refcount )
        rbuf_destroy( buf );
}

int rbuf_unique ( RBuf * buf ) {
    TATTLE_IF( buf == NULL );
    return buf->refcount == 1;
}

size_t rbuf_len ( RBuf * buf ) {
    TATTLE_IF( buf == NULL );
    return buf->len;
}

int rbuf_reserve ( RBuf * buf, size_t new_cap ) {
    TATTLE_IF( buf == NULL );
    if ( new_cap <= RILL_RBUF_MINSIZE )
        new_cap = RILL_RBUF_MINSIZE;
    if ( buf->cap >= new_cap )
        return 1;
    return __rbuf_resize( buf, new_cap );
}

int rbuf_compact ( RBuf * buf ) {
    TATTLE_IF( buf == NULL );
    size_t target = buf->len;
    if ( buf->cap == target + 1 )
        return 1;
    if ( target < RILL_RBUF_MINSIZE )
        target = RILL_RBUF_MINSIZE;
    return __rbuf_resize( buf, sizeof( char ) * target );
}

const char * rbuf_get ( RBuf * buf ) {
    TATTLE_IF( buf == NULL );
    return buf->buffer;
}

int rbuf_cpy ( RBuf * dst, RBuf * src ) {
    TATTLE_IF( dst == NULL );
    TATTLE_IF( src == NULL );
    if ( !rbuf_reserve( dst, src->len ) )
        return 0;
    memcpy( dst->buffer, src->buffer, src->len );
    dst->len = src->len;
    dst->buffer[ dst->len ] = 0;
    return 1;
}

int rbuf_cat ( RBuf * dst, RBuf * src ) {
    TATTLE_IF( dst == NULL );
    TATTLE_IF( src == NULL );
    size_t target_size = (
        ( ( double ) dst->len + ( double ) src->len ) *
        RILL_RBUF_GROWTHCOEFF
    );
    if ( !rbuf_reserve( dst, target_size ) )
        return 0;
    memcpy( dst->buffer + dst->len, src->buffer, src->len );
    dst->len += src->len;
    dst->buffer[ dst->len ] = 0;
    return 1;
}

int rbuf_cmp ( RBuf * a, RBuf * b ) {
    TATTLE_IF( a == NULL );
    TATTLE_IF( b == NULL );
    return memcmp( a->buffer, b->buffer, a->len );
}

int rbuf_cpyc ( RBuf * buf, const char * cstr ) {
    TATTLE_IF( buf == NULL );
    TATTLE_IF( cstr == NULL );
    size_t cstr_len = strlen( cstr );
    if ( !rbuf_reserve( buf, cstr_len ) )
        return 0;
    memcpy( buf->buffer, cstr, cstr_len );
    buf->len = cstr_len;
    buf->buffer[ buf->len ] = 0;
    return 1;
}

int rbuf_catc ( RBuf * buf, const char * cstr ) {
    TATTLE_IF( buf == NULL );
    TATTLE_IF( cstr == NULL );
    size_t cstr_len = strlen( cstr );
    size_t target_size = (
        ( ( double ) buf->len + ( double ) cstr_len ) *
        RILL_RBUF_GROWTHCOEFF
    );
    if ( !rbuf_reserve( buf, target_size ) )
        return 0;
    memcpy( buf->buffer + buf->len, cstr, cstr_len );
    buf->len += cstr_len;
    buf->buffer[ buf->len ] = 0;
    return 1;
}

int rbuf_cmpc ( RBuf * buf, const char * cstr ) {
    TATTLE_IF( buf == NULL );
    return memcmp( buf->buffer, cstr, buf->len );
}

void rbuf_clear ( RBuf * buf ) {
    TATTLE_IF( buf == NULL );
    buf->len = 0;
    buf->buffer[ 0 ] = 0;
}

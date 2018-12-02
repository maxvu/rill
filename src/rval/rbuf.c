#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "environment.h"
#include "rval/rbuf.h"

RBuf * rbuf_create ( size_t init_cap ) {
    RBuf * buf = RILL_ALLOC( sizeof( RBuf ) );
    if ( !buf )
        return NULL;
    if ( init_cap < RILL_RBUF_MINSIZE )
        init_cap = RILL_RBUF_MINSIZE;
    buf->buffer = RILL_ALLOC( init_cap + 1 );
    if ( buf->buffer ) {
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
    TATTLE( buf );
    TATTLE( buf->buffer );
    free( buf->buffer );
    free( buf );
}

void rbuf_ref ( RBuf * buf ) {

}

void rbuf_deref ( RBuf * buf ) {

}

int rbuf_unique ( RBuf * buf ) {

}

int rbuf_len ( RBuf * buf ) {

}

int rbuf_reserve ( RBuf * buf, size_t new_cap ) {

}

int rbuf_compact ( RBuf * buf ) {

}

const char * rbuf_get ( RBuf * buf ) {

}

int rbuf_cpy ( RBuf * dst, RBuf * src ) {

}

int rbuf_cat ( RBuf * dst, RBuf * src ) {

}

int rbuf_cmp ( RBuf * a, RBuf * b ) {

}

int rbuf_cpyc ( RBuf * buf, char * cstr, size_t cstr_len ) {

}

int rbuf_catc ( RBuf * buf, char * cstr, size_t cstr_len ) {

}

int rbuf_cmpc ( RBuf * buf, char * cstr ) {

}

void rbuf_clear ( RBuf * buf ) {

}

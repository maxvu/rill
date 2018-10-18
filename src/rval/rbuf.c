#include <assert.h>
#include <stdlib.h>

#include "rval/rval.h"
#include "rval/rbuf.h"

int __rbuf_resize ( RCtx * ctx, RBuf * buf, size_t new_cap ) {
    assert( ctx != NULL );
    assert( buf != NULL );
    assert( rval_type( buf ) == RVT_NIL );
    assert( new_cap >= RILL_VM_RBUF_MINSIZE );
    uint8_t * new_buf = ( uint8_t * ) malloc(
        sizeof( uint8_t ) * ( new_cap + 1 )
    );
    if ( !new_buf )
        return 0;
    if ( buf->buf != NULL && buf->len ) {
        memcpy( new_buf, buf->buf, buf->len );
        free( buf->buf );
    }
    new_buf[ buf->len ] = 0;
    buf->buf = new_buf;
    buf->cap = new_cap;
    return 1;
}

int rbuf_init ( RCtx * ctx, RVal * buf, size_t init_cap ) {
    assert( ctx != NULL );
    assert( buf != NULL );
    buf->type = buf;
}

int rbuf_reserve ( RCtx * ctx, RVal * buf, size_t new_cap ) {

}

int rbuf_compact ( RCtx * ctx, RVal * buf ) {

}

size_t rbuf_len ( RCtx * ctx, RVal * buf ) {

}

uint8_t * rbuf_get ( RCtx * ctx, RVal * buf ) {

}

char * rbuf_cstr ( RCtx * ctx, RVal * buf ) {

}

int rbuf_set ( RCtx * ctx, RVal * buf, RVal * other ) {

}

int rbuf_cat ( RCtx * ctx, RVal * buf, RVal * other ) {

}

int rbuf_cmp ( RCtx * ctx, RVal * buf, RVal * other ) {

}

int rbuf_setc ( RCtx * ctx, RVal * buf, const char * cstr, size_t cstr_len ) {

}

int rbuf_catc ( RCtx * ctx, RVal * buf, const char * cstr, size_t cstr_len ) {

}

int rbuf_cmpc ( RCtx * ctx, RVal * buf, const char * cstr, size_t cstr_len ) {

}

int rbuf_clear ( RCtx * ctx, RVal * buf ) {

}

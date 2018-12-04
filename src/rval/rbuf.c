#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "environment.h"
#include "rval/rbuf.h"

int ____rbuf_resize ( RBuf * buf, size_t new_cap ) {
    if ( buf == NULL ) {
        TATTLE;
        return 0;
    }
    new_cap++; // null terminator at maximum capacity
    if ( new_cap <= buf->len )
        TATTLE;
    new_cap = sizeof( char ) * new_cap;
    char * new_buffer = RILL_REALLOC( buf->buffer, new_cap );
    if ( new_buffer == NULL )
        return 0;
    buf->buffer = new_buffer;
    buf->cap = new_cap;
    return 1;
}

RBuf * __rbuf_create ( size_t init_cap ) {
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

void __rbuf_destroy ( RBuf * buf ) {
    if ( buf == NULL ) {
        TATTLE;
        return;
    }
    if ( buf->buffer == NULL ) {
        TATTLE;
        return;
    }
    free( buf->buffer );
    free( buf );
}

void __rbuf_lease ( RBuf * buf ) {
    if ( buf == NULL ) {
        TATTLE;
        return;
    }

    buf->refcount++;
}

void __rbuf_release ( RBuf * buf ) {
    if ( buf == NULL ) {
        TATTLE;
        return;
    }

    if ( !--buf->refcount )
        __rbuf_destroy( buf );
}

int __rbuf_unique ( RBuf * buf ) {
    if ( buf == NULL ) {
        TATTLE;
        return 0;
    }

    return buf->refcount == 1;
}

size_t __rbuf_len ( RBuf * buf ) {
    if ( buf == NULL ) {
        TATTLE;
        return 0;
    }

    return buf->len;
}

int __rbuf_reserve ( RBuf * buf, size_t new_cap ) {
    if ( buf == NULL ) {
        TATTLE;
        return 0;
    }
    if ( new_cap <= RILL_RBUF_MINSIZE )
        new_cap = RILL_RBUF_MINSIZE;
    if ( buf->cap >= new_cap )
        return 1;
    return ____rbuf_resize( buf, (double) new_cap * RILL_RBUF_GROWTHCOEFF );
}

int __rbuf_compact ( RBuf * buf ) {
    if ( buf == NULL ) {
        TATTLE;
        return 0;
    }
    size_t target = buf->len;
    if ( buf->cap == target + 1 )
        return 1;
    if ( target < RILL_RBUF_MINSIZE )
        target = RILL_RBUF_MINSIZE;
    return ____rbuf_resize( buf, target );
}

const char * __rbuf_get ( RBuf * buf ) {
    if ( buf == NULL ) {
        TATTLE;
        return 0;
    }
    return buf->buffer;
}

int __rbuf_cpy ( RBuf * dst, RBuf * src ) {
    if ( dst == NULL ) {
        TATTLE;
        return 0;
    }
    if ( src == NULL ) {
        TATTLE;
        return 0;
    }
    if ( !__rbuf_reserve( dst, src->len ) )
        return 0;
    memcpy( dst->buffer, src->buffer, src->len );
    dst->len = src->len;
    dst->buffer[ dst->len ] = 0;
    return 1;
}

int __rbuf_cat ( RBuf * dst, RBuf * src ) {
    if ( dst == NULL ) {
        TATTLE;
        return 0;
    }
    if ( src == NULL ) {
        TATTLE;
        return 0;
    }
    if ( !__rbuf_reserve( dst, dst->len + src->len ) )
        return 0;
    memcpy( dst->buffer + dst->len, src->buffer, src->len );
    dst->len += src->len;
    dst->buffer[ dst->len ] = 0;
    return 1;
}

int __rbuf_cmp ( RBuf * a, RBuf * b ) {
    if ( a == NULL ) {
        TATTLE;
        return 0;
    }
    if ( b == NULL ) {
        TATTLE;
        return 0;
    }
    return memcmp( a->buffer, b->buffer, a->len );
}

int __rbuf_cpyc ( RBuf * buf, const char * cstr ) {
    if ( buf == NULL ) {
        TATTLE;
        return 0;
    }
    if ( cstr == NULL ) {
        TATTLE;
        return 0;
    }
    size_t cstr_len = strlen( cstr );
    if ( !__rbuf_reserve( buf, cstr_len ) )
        return 0;
    memcpy( buf->buffer, cstr, cstr_len );
    buf->len = cstr_len;
    buf->buffer[ buf->len ] = 0;
    return 1;
}

int __rbuf_catc ( RBuf * buf, const char * cstr ) {
    if ( buf == NULL ) {
        TATTLE;
        return 0;
    }
    if ( cstr == NULL ) {
        TATTLE;
        return 0;
    }
    size_t cstr_len = strlen( cstr );
    if ( !__rbuf_reserve( buf, buf->len + cstr_len ) )
        return 0;
    memcpy( buf->buffer + buf->len, cstr, cstr_len );
    buf->len += cstr_len;
    buf->buffer[ buf->len ] = 0;
    return 1;
}

int __rbuf_cmpc ( RBuf * buf, const char * cstr ) {
    if ( buf == NULL ) {
        TATTLE;
        return 0;
    }
    return memcmp( buf->buffer, cstr, buf->len );
}

void __rbuf_clear ( RBuf * buf ) {
    if ( buf == NULL ) {
        TATTLE;
        return;
    }
    buf->len = 0;
    buf->buffer[ 0 ] = 0;
}

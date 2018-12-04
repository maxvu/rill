#ifndef RILL_RVAL_RBUF
#define RILL_RVAL_RBUF

#include <stdlib.h>

#define RILL_RBUF_MINSIZE 8
#define RILL_RBUF_GROWTHCOEFF 2.0

typedef struct RBuf {
    char * buffer;
    size_t len;
    size_t cap;
    size_t refcount;
} RBuf;

// int __rbuf_resize ( RBuf * buf, size_t new_cap );

RBuf * __rbuf_create ( size_t init_cap );
void __rbuf_destroy ( RBuf * buf );

void __rbuf_lease ( RBuf * buf );
void __rbuf_release ( RBuf * buf );
int __rbuf_unique ( RBuf * buf );

size_t __rbuf_len ( RBuf * buf );
int __rbuf_reserve ( RBuf * buf, size_t new_cap );
int __rbuf_compact ( RBuf * buf );

const char * __rbuf_get ( RBuf * buf );

int __rbuf_cpy ( RBuf * dst, RBuf * src );
int __rbuf_cat ( RBuf * dst, RBuf * src );
int __rbuf_cmp ( RBuf * a, RBuf * b );

int __rbuf_cpyc ( RBuf * buf, const char * cstr );
int __rbuf_catc ( RBuf * buf, const char * cstr );
int __rbuf_cmpc ( RBuf * buf, const char * cstr );

void __rbuf_clear ( RBuf * buf );

#endif

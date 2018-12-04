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

RBuf * rbuf_create ( size_t init_cap );
void rbuf_destroy ( RBuf * buf );

void rbuf_lease ( RBuf * buf );
void rbuf_release ( RBuf * buf );
int rbuf_unique ( RBuf * buf );

size_t rbuf_len ( RBuf * buf );
int rbuf_reserve ( RBuf * buf, size_t new_cap );
int rbuf_compact ( RBuf * buf );

const char * rbuf_get ( RBuf * buf );

int rbuf_cpy ( RBuf * dst, RBuf * src );
int rbuf_cat ( RBuf * dst, RBuf * src );
int rbuf_cmp ( RBuf * a, RBuf * b );

int rbuf_cpyc ( RBuf * buf, const char * cstr );
int rbuf_catc ( RBuf * buf, const char * cstr );
int rbuf_cmpc ( RBuf * buf, const char * cstr );

void rbuf_clear ( RBuf * buf );

#endif

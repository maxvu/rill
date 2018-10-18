#ifndef RILL_RVAL_RBUF
#define RILL_RVAL_RBUF

#include <stddef.h>
#include <stdint.h>

typedef struct RCtx RCtx;
typedef struct RVal RVal;

/*
    Combination byte-buffer / C-string.
    Will ensure null-termination.
*/

#define RILL_VM_RBUF_MINSIZE 8
#define RILL_VM_RBUF_GROWTHCOEFF 2.0

typedef struct RBuf {
    uint8_t * buf;
    size_t len;
    size_t cap;
} RBuf;

int __rbuf_resize ( RCtx * ctx, RBuf * buf, size_t new_cap );

int rbuf_create ( RVal * buf, size_t init_cap );
void rbuf_destroy ( RVal * buf );

int rbuf_init ( RCtx * ctx, RVal * buf, size_t init_cap );
int rbuf_reserve ( RCtx * ctx, RVal * buf, size_t new_cap );
int rbuf_compact ( RCtx * ctx, RVal * buf );
size_t rbuf_len ( RCtx * ctx, RVal * buf );
uint8_t * rbuf_get ( RCtx * ctx, RVal * buf );
char * rbuf_cstr ( RCtx * ctx, RVal * buf );
int rbuf_set ( RCtx * ctx, RVal * buf, RVal * other );
int rbuf_cat ( RCtx * ctx, RVal * buf, RVal * other );
int rbuf_cmp ( RCtx * ctx, RVal * buf, RVal * other );
int rbuf_setc ( RCtx * ctx, RVal * buf, const char * cstr, size_t cstr_len );
int rbuf_catc ( RCtx * ctx, RVal * buf, const char * cstr, size_t cstr_len );
int rbuf_cmpc ( RCtx * ctx, RVal * buf, const char * cstr, size_t cstr_len );
int rbuf_clear ( RCtx * ctx, RVal * buf );

#endif

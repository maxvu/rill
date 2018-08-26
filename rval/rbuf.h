#ifndef RILL_RVAL_RBUF
#define RILL_RVAL_RBUF

/*
    Combination byte-buffer / C-string.
    Will ensure null-termination.
*/

typedef struct RBuf {
    uint8_t * buf;
    size_t len;
    size_t cap;
} RBuf;

int __rbuf_resize ( RBuf * buf, size_t new_cap );

int rbuf_init ( RBuf * buf, size_t init_cap );
size_t rbuf_len ( RBuf * buf );
int rbuf_reserve ( RBuf * buf, size_t new_cap );
int rbuf_compact ( RBuf * buf );
uint8_t * rbuf_get ( RBuf * buf );
char * rbuf_getc ( RBuf * buf );
int rbuf_set ( RBuf * buf, const uint8_t * cts, size_t cts_len );
int rbuf_concat ( RBuf * buf, const uint8_t * sfx, size_t sfx_len );
int rbuf_cmp ( RBuf * buf, const uint8_t * cts, size_t cts_len );
void rbuf_clear ( RBuf * buf );
void rbuf_retire ( RBuf * buf, size_t init_cap );

#endif

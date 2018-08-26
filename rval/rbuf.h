#ifndef RILL_RVAL_RBUF
#define RILL_RVAL_RBUF

typedef struct RBuf {
    char * buf;
    size_t len;
    size_t cap;
} RBuf;

int rbuf_init ( RBuf & buf, size_t init_cap );
size_t rbuf_len ( RBuf & buf );
int rbuf_reserve ( RBuf & buf, size_t new_cap );
int rbuf_compact ( RBuf & buf, size_t new_cap );
int rbuf_set ( RBuf & buf, const char * cts, size_t cts_len );
int rbuf_concat ( RBuf & buf, const char * sfx, size_t sfx_len );
int rbuf_retire ( RBuf & buf, size_t init_cap );

#endif

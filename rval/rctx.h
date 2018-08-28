#ifndef RILL_RVAL_RCTX
#define RILL_RVAL_RCTX

typedef struct RVal RVal;

typedef struct RCtx {
    RVal bufs;
    RVal vecs;
    RVal maps;
} RCtx;

RCtx * rctx_create ();
RBuf * rctx_alloc_buf ( size_t init_cap );
RVec * rctx_alloc_vec ( size_t init_cap );
RMap * rctx_alloc_map ( size_t init_cap );
void * rctx_reclaim ( RVal * val );
void rctx_destroy ( RCtx * ctx );

#endif

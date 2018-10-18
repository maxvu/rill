#ifndef RILL_RVAL_RCTX
#define RILL_RVAL_RCTX

#include <stddef.h>

typedef struct RVal RVal;
typedef struct RBuf RBuf;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef struct RCtx {
    int ___;
} RCtx;

RCtx * rctx_create ();
RBuf * rctx_alloc_buf ( size_t init_cap );
RVec * rctx_alloc_vec ( size_t init_cap );
RMap * rctx_alloc_map ( size_t init_cap );
void * rctx_reclaim ( RVal * val );
void rctx_destroy ( RCtx * ctx );

#endif

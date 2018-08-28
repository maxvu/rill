#ifndef RILL_RVAL_RVEC
#define RILL_RVAL_RVEC

typedef struct RCtx RCtx;
typedef struct RVal RVal;

typedef struct RVec {
    RVal * vals;
    size_t len;
    size_t cap;
} RVec;

int rvec_init ( RCtx * ctx, RVec * vec );
size_t rvec_len ( RCtx * ctx, RVec * vec );
int rvec_reserve ( RCtx * ctx, RVec * vec, size_t new_cap );
int rvec_compact ( RCtx * ctx, RVec * vec );
int rvec_get ( RCtx * ctx, RVec * vec, size_t idx );
int rvec_set ( RCtx * ctx, RVec * vec, size_t idx, RVal * item );
int rvec_push ( RCtx * ctx, RVec * vec, RVal * item );
int rvec_pop ( RCtx * ctx, RVec * vec );
int rvec_clear ( RCtx * ctx, RVec * vec );
int rvec_retire ( RCtx * ctx, RVec * vec );

#endif

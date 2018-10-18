#ifndef RILL_RVAL_RVAL
#define RILL_RVAL_RVAL

typedef struct RCtx RCtx;
typedef struct RVal RVal;
typedef struct RBuf RBuf;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef enum RValType {
    RVT_NIL = 0,
    RVT_UXX = 1,
    RVT_IXX = 2,
    RVT_DBL = 3,
    RVT_BUF = 4,
    RVT_VEC = 5,
    RVT_MAP = 10
} RValType;

typedef struct RVal {
    enum RValType type;
    union {
        unsigned long uxx;
        long          ixx;
        double        fxx;
        RBuf *        buf;
        RVec *        vec;
        RMap *        map;
        void *        udo;
    };
} RVal;

void rval_fzero ( RVal * val );
RValType rval_type ( RVal * val );
int rval_copy ( RCtx * ctx, RVal * dst, RVal * src );
int rval_clone ( RCtx * ctx, RVal * dst, RVal * src );
int rval_compact ( RCtx * ctx, RVal * val );
int rval_lease ( RCtx * ctx, RVal * val );
int rval_clear ( RCtx * ctx, RVal * val );

#endif

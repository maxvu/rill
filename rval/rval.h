#ifndef RILL_RVAL_RVAL
#define RILL_RVAL_RVAL

typedef struct RCtx RCtx;
typedef struct RVal RVal;
typedef struct RBuf RBuf;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef enum RValType {
    NIL = 0,
    UXX = 1,
    IXX = 2,
    DBL = 3,
    BUF = 4,
    VEC = 5,
    MAP = 10
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

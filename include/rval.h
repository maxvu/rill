#ifndef RILL_RVAL
#define RILL_RVAL

#include "rerr.h"

typedef struct rval {
    UXX hed;
} rval;

typedef struct rnum {
    UXX    hed;
    union {
        IXX ixx;
        UXX uxx;
        FXX fxx;
    };
} rnum;

typedef struct rstr {
    UXX    hed;
    UXX    len;
    UXX    cap;
    char * buf;
} rstr;

typedef struct rvec {
    UXX    hed;
    UXX    len;
    UXX    cap;
    rval * vls;
} rvec;

typedef struct rmap_slot {
    rval key;
    rval val;
} rmap_slot;

typedef struct rmapit {
    rmap_slot * pos;
    rmap_slot * end;
} rmapit;

typedef struct rmap {
    UXX         hed;
    UXX         len;
    UXX         cap;
    rmap_slot * sts;
} rmap;

void rval_type     ( rval * val, UXX * out, rerr * err );
void rval_tag      ( rval * val, UXX * out, rerr * err );
void rval_set_tag  ( rval * val, UXX tag, rerr * err );
void rval_ref      ( rvctx * ctx, rval ** val, rerr * err );
void rval_deref    ( rvctx * ctx, rval ** val, rerr * err );
void rval_compact  ( rvctx * ctx, rval * val, rerr * err );
void rval_contains ( rval * hay, rval * ndl, char * out, rerr * err );
void rval_equals   ( rval * a, rval * b, char * out, rerr * err );
void rval_copy     ( rval ** dst, rval ** src, rerr * err );
void rval_move     ( rval ** dst, rval ** src, rerr * err );

#endif

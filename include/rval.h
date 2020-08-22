#ifndef RILL_RVAL
#define RILL_RVAL

#include "platform.h"
#include "rerr.h"

enum rval_types : UXX {
    RVT_NUM = 0,
    RVT_STR = 1,
    RVT_VEC = 2,
    RVT_MAP = 3,
    RVT_EXT = 7
};

typedef struct rval rval;

UXX    rval_type     ( rval * val, rerr * err );
rval * rval_clone    ( rval * src, rerr * err );
IXX    rval_contains ( rval * hay, rval * ndl, rerr * err );
rval * rval_ref      ( rval * val, rerr * err );
void   rval_deref    ( rval * val );

#endif

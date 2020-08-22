#ifndef RILL_RNUM
#define RILL_RNUM

#include "platform.h"
#include "rerr.h"

typedef struct rval rval;

/*
    The `rnum` houses the boxed and union'ed:
        - signed integer
        - unsigned integer and
        - floating-point types.

    Disparate-type access is allowed.
*/

rval * rnum_create ( rerr * err );
IXX    rnum_geti   ( rval * num, rerr * err );
rval * rnum_seti   ( rval * num, IXX    i,  rerr * err );
UXX    rnum_getu   ( rval * num, rerr * err );
rval * rnum_setu   ( rval * num, UXX    u,  rerr * err );
FXX    rnum_getf   ( rval * num, rerr * err );
rval * rnum_setf   ( rval * num, FXX    f,  rerr * err );

#endif

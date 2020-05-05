#ifndef RILL_RVAL
#define RILL_RVAL

#include "rerr.h"

typedef enum rval_type {
    RVT_IXX = 0,  // signed integer
    RVT_UXX = 1,  // unsigned integer
    RVT_FXX = 2,  // floating point
    RVT_STR = 3,  // string
    RVT_VEC = 4,  // vector
    RVT_MAP = 5,  // hashtable
    RVT_PIP = 6,  // pipe
    RVT_EXT = 7   // extension type
} rval_type;

typedef struct rval {
    rval_type typ;
} rval;

rval * rval_create ( rval_type typ );
rval_type rval_type ( rval * val );
void rval_lease ( rval * val );
void rval_release ( rval ** val );
rerr rval_copy ( rval ** dst, rval ** src );
rerr rval_detach ( rval ** val );
void rval_cyclesto ( rval * hay, rval * ndl );

rval * rnum_create ();
rerr rixx_set ( rval * num, IXX i );
rerr ruxx_set ( rval * num, UXX u );
rerr rfxx_set ( rval * num, FXX f );
IXX rixx_get ( rval * num );
UXX ruxx_get ( rval * num );
FXX rfxx_get ( rval * num );

#endif

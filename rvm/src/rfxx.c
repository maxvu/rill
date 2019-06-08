#include "rfxx.h"
#include "rerr.h"

#include <math.h>

rval rfxxq ( double f ) {
    return ( rval ) {
        .info = RVT_FXX,
        .fxx  = f
    };
}

rerr rfxx_set ( rval * val, double f ) {
    ASSERT_NOT_NULL( val );
    if ( !IS_FXX( val ) )
        rval_release( val );
    *val = ( rval ) {
        .info = RVT_FXX,
        .fxx  = f
    };
    return RERR_OK;
}

double rfxx_get ( rval * val ) {
    if ( !val )
        return 0.0;
    if ( !IS_FXX( val ) )
        return NAN;
    return val->fxx;
}

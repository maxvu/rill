#include "rfxx.h"
#include "rerr.h"

#include <math.h>

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
    ASSERT_NOT_NULL( val );
    if ( !IS_FXX( val ) )
        return NAN;
    return val->fxx;
}

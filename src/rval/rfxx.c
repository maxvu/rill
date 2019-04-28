#include "config/rerr.h"
#include "rval/rfxx.h"
#include "rval/rval.h"

#include <math.h>

rval rfxx ( RILL_FXX_TYPE f ) {
    return ( rval ) {
        .typ = RVT_FXX,
        .fxx = f
    };
}

void rfxx_set ( rval * val, RILL_FXX_TYPE f ) {
    if ( !val ) return;
    *val = ( rval ) {
        .typ = RVT_FXX,
        .fxx = f
    };
}

RILL_FXX_TYPE rfxx_get ( rval * val ) {
    RILL_ASSERT_ISFXX( val );
    return val->fxx;
}

int rfxx_isfinite ( rval * val ) {
    RILL_ASSERT_ISFXX( val );
    return isfinite( val->fxx );
}

int rfxx_isinf ( rval * val ) {
    RILL_ASSERT_ISFXX( val );
    return isinf( val->fxx );
}

int rfxx_isnan ( rval * val ) {
    RILL_ASSERT_ISFXX( val );
    return isnan( val->fxx );
}

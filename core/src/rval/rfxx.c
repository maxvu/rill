#include "config/rerr.h"
#include "rval/rfxx.h"
#include "rval/rval.h"

#include <math.h>

RVal rfxx ( RILL_FXX_TYPE f ) {
    return ( RVal ) {
        .typ = RVT_FXX,
        .fxx = f
    };
}

void rfxx_set ( RVal * val, RILL_FXX_TYPE f ) {
    if ( !val ) return;
    *val = ( RVal ) {
        .typ = RVT_FXX,
        .fxx = f
    };
}

RILL_FXX_TYPE rfxx_get ( RVal * val ) {
    RILL_ASSERT_ISFXX( val );
    return val->fxx;
}

int rfxx_isfinite ( RVal * val ) {
    RILL_ASSERT_ISFXX( val );
    return isfinite( val->fxx );
}

int rfxx_isinf ( RVal * val ) {
    RILL_ASSERT_ISFXX( val );
    return isinf( val->fxx );
}

int rfxx_isnan ( RVal * val ) {
    RILL_ASSERT_ISFXX( val );
    return isnan( val->fxx );
}

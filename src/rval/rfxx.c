#include "rval/rfxx.h"

RVal rfxx ( RILL_FXX_TYPE f ) {
    RVal val;
    val.info = RVT_FXX;
    val.fxx = f;
    return val;
}

RILL_FXX_TYPE rfxx_get ( RVal * val ) {
    RILL_RVAL_ENFORCETYPE( val, RVT_FXX ) { return 0.0; }
    return val->fxx;
}

void rfxx_set ( RVal * val, RILL_FXX_TYPE f ) {
    rval_release( val );
    *val = rfxx( f );
}
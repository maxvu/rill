#include "config/rerr.h"
#include "rval/ruxx.h"
#include "rval/rval.h"

rval ruxx ( RILL_UXX_TYPE u ) {
    return ( rval ) {
        .typ = RVT_UXX,
        .uxx = u
    };
}

void ruxx_set ( rval * val, RILL_UXX_TYPE u ) {
    if ( !val ) return;
    *val = ( rval ) {
        .typ = RVT_UXX,
        .uxx = u
    };
}

RILL_UXX_TYPE ruxx_get ( rval * val ) {
    RILL_ASSERT_ISUXX( val );
    return val->uxx;
}

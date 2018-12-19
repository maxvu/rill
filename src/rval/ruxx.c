#include "rval/rval.h"
#include "rval/ruxx.h"

RVal ruxx ( RILL_UXX_TYPE u ) {
    RVal val;
    val.info = RVT_UXX;
    val.uxx = u;
    return val;
}

RILL_UXX_TYPE ruxx_get ( RVal * val ) {
    RILL_RVAL_ENFORCETYPE( val, RVT_UXX ) { return 0; }
    return val->uxx;
}

void ruxx_set ( RVal * val, RILL_UXX_TYPE u ) {
    rval_release( val );
    *val = ruxx( u );
}

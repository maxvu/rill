#include "rval/rval.h"
#include "rval/ruxx.h"

RVal ruxx ( RILL_UXX_TYPE u ) {
    return ( RVal ){
        .info = RVT_UXX,
        .uxx = u
    };
}

RILL_UXX_TYPE ruxx_get ( RVal * val ) {
    RILL_RVAL_ENFORCETYPE( val, RVT_UXX ) { return 0; }
    return val->uxx;
}

void ruxx_set ( RVal * val, RILL_UXX_TYPE u ) {
    rval_release( val );
    *val = ruxx( u );
}

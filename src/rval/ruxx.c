#include "rval/ruxx.h"
#include "rval/rval.h"

RVal ruxx ( RILL_UXX_TYPE u ) {
    return ( RVal ) {
        .typ = RVT_UXX,
        .uxx = u
    };
}

void ruxx_set ( RVal * val, RILL_UXX_TYPE u ) {
    if ( !val ) return;
    *val = ( RVal ) {
        .typ = RVT_UXX,
        .uxx = u
    };
}

RILL_UXX_TYPE ruxx_get ( RVal * val ) {
    if ( !val || rval_type( val ) != RVT_UXX )
        return 0;
    return val->uxx;
}

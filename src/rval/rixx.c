#include "rval/rval.h"
#include "rval/rixx.h"

RVal rixx ( RILL_IXX_TYPE i ) {
    return ( RVal ){
        .info = RVT_IXX,
        .ixx = i
    };
}

RILL_IXX_TYPE rixx_get ( RVal * val ) {
    RILL_RVAL_ENFORCETYPE( val, RVT_IXX ) { return 0; }
    return val->ixx;
}

void rixx_set ( RVal * val, RILL_IXX_TYPE i ) {
    rval_release( val );
    *val = rixx( i );
}

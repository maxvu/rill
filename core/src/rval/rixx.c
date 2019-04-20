#include "config/rerr.h"
#include "rval/rixx.h"
#include "rval/rval.h"

RVal rixx ( RILL_IXX_TYPE i ) {
    return ( RVal ) { .typ = RVT_IXX, .ixx = i };
}

void rixx_set ( RVal * val, RILL_IXX_TYPE i ) {
    if ( !val ) return;
    *val = ( RVal ) { .typ = RVT_IXX, .ixx = i };
}

RILL_IXX_TYPE rixx_get ( RVal * val ) {
    RILL_ASSERT_ISIXX( val );
    return val->ixx;
}

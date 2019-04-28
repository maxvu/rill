#include "config/rerr.h"
#include "rval/rixx.h"
#include "rval/rval.h"

rval rixx ( RILL_IXX_TYPE i ) {
    return ( rval ) { .typ = RVT_IXX, .ixx = i };
}

void rixx_set ( rval * val, RILL_IXX_TYPE i ) {
    if ( !val ) return;
    *val = ( rval ) { .typ = RVT_IXX, .ixx = i };
}

RILL_IXX_TYPE rixx_get ( rval * val ) {
    RILL_ASSERT_ISIXX( val );
    return val->ixx;
}

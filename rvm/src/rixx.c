#include "rerr.h"
#include "rixx.h"
#include "rval.h"

rval rixxq ( int i ) {
    return ( rval ) {
        .info = RVT_IXX,
        .ixx  = i
    };
}

rerr rixx_set ( rval * val, int i ) {
    ASSERT_NOT_NULL( val );
    if ( !IS_IXX( val ) )
        rval_release( val );
    *val = rixxq( i );
    return RERR_OK;
}

int rixx_get ( rval * val ) {
    ASSERT_NOT_NULL( val );
    if ( !IS_IXX( val ) )
        return 0;
    return val->ixx;
}

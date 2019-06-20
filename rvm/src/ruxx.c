#include "rerr.h"
#include "ruxx.h"
#include "rval.h"

rval ruxxq ( unsigned int i ) {
    return ( rval ) {
        .info = RVT_UXX,
        .uxx  = i
    };
}

rerr ruxx_set ( rval * val, unsigned int i ) {
    ASSERT_NOT_NULL( val );
    if ( !IS_UXX( val ) )
        rval_release( val );
    *val = ruxxq( i );
    return RERR_OK;
}

unsigned int ruxx_get ( rval * val ) {
    ASSERT_NOT_NULL( val );
    if ( !IS_UXX( val ) )
        return 0;
    return val->uxx;
}
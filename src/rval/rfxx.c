#include "rval/rval.h"
#include "rval/rfxx.h"

double rfxx_get ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_FXX );
    return val->fxx;
}

void rfxx_set ( RVal * val, double u ) {
    assert( val );
    if ( rval_type( val ) != RVT_FXX )
        rval_zero( val );
    val->type = RVT_FXX;
    val->fxx = u;
}

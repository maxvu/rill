#include "rval/rval.h"
#include "rval/ruxx.h"

unsigned long ruxx_get ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_UXX );
    return val->uxx;
}

void ruxx_set ( RVal * val, unsigned long u ) {
    assert( val );
    if ( rval_type( val ) != RVT_UXX )
        rval_zero( val );
    val->type = RVT_UXX;
    val->uxx = u;
}

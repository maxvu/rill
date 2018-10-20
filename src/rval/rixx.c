#include "rval/rval.h"
#include "rval/rixx.h"

long rixx_get ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_IXX );
    return val->ixx;
}

void rixx_set ( RVal * val, long u ) {
    assert( val );
    if ( rval_type( val ) != RVT_IXX )
        rval_zero( val );
    val->ixx = u;
}

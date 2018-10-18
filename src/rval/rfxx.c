#include "rval/rval.h"
#include "rval/rfxx.h"

#include <assert.h>
#include <stddef.h>

long rfxx_get ( RVal * val ) {
    assert( val != NULL );
    assert( rval_type( val ) );
    return val->fxx;
}

void rfxx_set ( RVal * val, double f ) {
    assert( val != NULL );
    assert( rval_type( val ) );
    val->fxx = f;
}

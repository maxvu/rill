#include "rval/rval.h"
#include "rval/rixx.h"

#include <assert.h>
#include <stddef.h>

long rixx_get ( RVal * val ) {
    assert( val != NULL );
    assert( rval_type( val ) );
    return val->ixx;
}

void rixx_set ( RVal * val, long i ) {
    assert( val != NULL );
    assert( rval_type( val ) );
    val->ixx = i;
}

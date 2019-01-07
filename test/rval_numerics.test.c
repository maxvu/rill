#include "test.h"
#include "rval.h"

void rill_test_rval_numerics () {

    RTEST_BEGIN("rval / numerics / access") {

    {
        RVal a = rixx( 1 );
        RVal b = rixx( 3 );

        INSIST( rixx_get( &a ) + rixx_get( &b ) == 4 );
    }

    } RTEST_END;

}

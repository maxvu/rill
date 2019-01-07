#include "test.h"
#include "rval.h"

void rill_test_rval_numerics () {

    RTEST_BEGIN("rval / numerics / access") {

    {
        RVal a = rixx( 1 );
        RVal b = rixx( 3 );
        INSIST( rval_type( &a ) == RVT_IXX );
        INSIST( rixx_get( &a ) + rixx_get( &b ) == 4 );
    }

    {
        RVal a = ruxx( 2 );
        RVal b = ruxx( 7 );
        INSIST( rval_type( &a ) == RVT_UXX );
        INSIST( ruxx_get( &a ) + ruxx_get( &b ) == 9 );
    }

    {
        RVal a = rfxx( 22.0 );
        RVal b = rfxx( 11.0 );
        INSIST( rval_type( &a ) == RVT_FXX );
        INSIST( rfxx_get( &a ) + rfxx_get( &b ) - 33.0 < 0.001 );
        INSIST( rfxx_isfinite( &a ) );
    }

    } RTEST_END;

}

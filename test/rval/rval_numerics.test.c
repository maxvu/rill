#include "test/test.h"
#include "rval/rixx.h"
#include "rval/ruxx.h"
#include "rval/rfxx.h"
#include "rval/rval.h"

void rill_test_rval_numerics () {

    RTEST_BEGIN( "rval / numerics / rixx access" )  {
        rval a = rixx( 1 );
        rval b = rixx( 3 );
        INSIST( rval_type( &a ) == RVT_IXX );
        INSIST( rixx_get( &a ) + rixx_get( &b ) == 4 );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / ruxx access" )  {
        rval a = ruxx( 2 );
        rval b = ruxx( 7 );
        INSIST( rval_type( &a ) == RVT_UXX );
        INSIST( ruxx_get( &a ) + ruxx_get( &b ) == 9 );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / rfxx access" ) {
        rval a = rfxx( 22.0 );
        rval b = rfxx( 11.0 );
        INSIST( rval_type( &a ) == RVT_FXX );
        INSIST( rfxx_get( &a ) + rfxx_get( &b ) - 33.0 < 0.001 );
        INSIST( rfxx_isfinite( &a ) );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / copy()" )  {
        rval a = ruxx( 9 );
        rval b = rnil();
        INSIST( rval_copy( &b, &a ) );
        INSIST( rval_eq( &b, &a ) );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / clone()" )  {
        rval a = rixx( 22 );
        rval b = rnil();
        INSIST( rval_clone( &b, &a ) );
        INSIST( rval_eq( &b, &a ) );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / clone()" )  {
        rval ixx_true = rixx( 22 );
        rval ixx_false = rixx( 0 );
        rval uxx_true = rixx( 78 );
        rval uxx_false = rixx( 0 );
        rval fxx_true = rfxx( 1.2 );
        rval fxx_false = rfxx( 0.0 );

        INSIST( rval_truthy( &ixx_true ) );
        INSIST( rval_truthy( &uxx_true ) );
        INSIST( rval_truthy( &fxx_true ) );

        INSIST( !rval_truthy( &ixx_false ) );
        INSIST( !rval_truthy( &uxx_false ) );
        INSIST( !rval_truthy( &fxx_false ) );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / cyclesto()" )  {
        rval a = rixx( 22 );
        rval b = ruxx( 9 );
        INSIST( !rval_cyclesto( &b, &a ) );
        INSIST( !rval_cyclesto( &a, &b ) );
    } RTEST_END;

}

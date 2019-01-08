#include "test.h"
#include "rval.h"

void rill_test_rval_numerics () {

    RTEST_BEGIN( "rval / numerics / rixx access" )  {
        RVal a = rixx( 1 );
        RVal b = rixx( 3 );
        INSIST( rval_type( &a ) == RVT_IXX );
        INSIST( rixx_get( &a ) + rixx_get( &b ) == 4 );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / ruxx access" )  {
        RVal a = ruxx( 2 );
        RVal b = ruxx( 7 );
        INSIST( rval_type( &a ) == RVT_UXX );
        INSIST( ruxx_get( &a ) + ruxx_get( &b ) == 9 );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / rfxx access" ) {
        RVal a = rfxx( 22.0 );
        RVal b = rfxx( 11.0 );
        INSIST( rval_type( &a ) == RVT_FXX );
        INSIST( rfxx_get( &a ) + rfxx_get( &b ) - 33.0 < 0.001 );
        INSIST( rfxx_isfinite( &a ) );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / copy()" )  {
        RVal a = ruxx( 9 );
        RVal b = rnil();
        INSIST( rval_copy( &b, &a ) );
        INSIST( rval_eq( &b, &a ) );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / clone()" )  {
        RVal a = rixx( 22 );
        RVal b = rnil();
        INSIST( rval_clone( &b, &a ) );
        INSIST( rval_eq( &b, &a ) );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / clone()" )  {
        RVal ixx_true = rixx( 22 );
        RVal ixx_false = rixx( 0 );
        RVal uxx_true = rixx( 78 );
        RVal uxx_false = rixx( 0 );
        RVal fxx_true = rfxx( 1.2 );
        RVal fxx_false = rfxx( 0.0 );

        INSIST( rval_truthy( &ixx_true ) );
        INSIST( rval_truthy( &uxx_true ) );
        INSIST( rval_truthy( &fxx_true ) );

        INSIST( !rval_truthy( &ixx_false ) );
        INSIST( !rval_truthy( &uxx_false ) );
        INSIST( !rval_truthy( &fxx_false ) );
    } RTEST_END;

    RTEST_BEGIN( "rval / numerics / cyclesto()" )  {
        RVal a = rixx( 22 );
        RVal b = ruxx( 9 );
        INSIST( !rval_cyclesto( &b, &a ) );
        INSIST( !rval_cyclesto( &a, &b ) );
    } RTEST_END;

}

#include "environment.h"
#include "rill_test.h"

#include "rval/rvec.h"

void test_rval_rvec () {

    TEST_BEGIN( "rvec / init" ) {
        RVec * vec = rvec_create( 10 );
        INSIST( rvec_len( vec ) == 0 );
        INSIST( rvec_unique( vec ) );
        rvec_destroy( vec );
    } TEST_END

    // TEST_BEGIN( "rvec / ops" ) {
    //     RVec * a = rvec_create( 10 );
    //     RVec * b = rvec_create( 10 );
    //     RRef c = rref_nil();
    //
    //     for ( size_t i = 0; i < 100; i++ ) {
    //         if ( i % 3 == 0 && i % 5 == 0 )
    //             INSIST( rvec_push( a,  ) );
    //     }
    //
    //     rvec_destroy( a );
    //     rvec_destroy( b );
    // } TEST_END

}
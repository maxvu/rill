#include "environment.h"
#include "rill_test.h"

#include "rval/rvec.h"

void test_rval_rvec () {

    TEST_BEGIN( "rvec / init" ) {
        RVec * vec = __rvec_create( 10 );
        INSIST( __rvec_len( vec ) == 0 );
        INSIST( __rvec_unique( vec ) );
        __rvec_destroy( vec );
    } TEST_END

    // TEST_BEGIN( "__rvec / ops" ) {
    //     RVec * a = __rvec_create( 10 );
    //     RVec * b = __rvec_create( 10 );
    //     RRef c = rref_nil();
    //
    //     for ( size_t i = 0; i < 100; i++ ) {
    //         if ( i % 3 == 0 && i % 5 == 0 )
    //             INSIST( __rvec_push( a,  ) );
    //     }
    //
    //     __rvec_destroy( a );
    //     __rvec_destroy( b );
    // } TEST_END

}

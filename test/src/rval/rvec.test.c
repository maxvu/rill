#include "environment.h"
#include "rill_test.h"

#include "rval/rref.h"
#include "rval/rnum.h"
#include "rval/rvec.h"

void test_rval_rvec () {

    TEST_BEGIN( "rvec / init" ) {
        RVec * vec = __rvec_create( 10 );
        INSIST( __rvec_len( vec ) == 0 );
        INSIST( __rvec_unique( vec ) );
        __rvec_destroy( vec );
    } TEST_END

    TEST_BEGIN( "__rvec / ops" ) {
        RVec * a = __rvec_create( 10 );
        RVec * b = __rvec_create( 10 );
        RRef c = rref_uxx( 0 );

        for ( size_t i = 0; i < 50; i++ ) {
            __ruxx_set( &c, i );
            if ( i % 2 == 0 ) {
                INSIST( __rvec_push( a, &c ) );
            } else {
                INSIST( __rvec_push( b, &c ) );
            }
        }

        // INSIST( __rvec_len( a ) == 50 );
        // INSIST( __rvec_len( b ) == 50 );
        // RRef * xx = __rvec_get( b, 48 );
        // INSIST( __ruxx_get( xx ) == 99 );

        __rvec_destroy( a );
        __rvec_destroy( b );
    } TEST_END

}

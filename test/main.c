#include "rill_test.h"
#include "rval_test.h"

#include <stdio.h>

void rill_rval_test () {
    // rill_rval_rval_test ();
    rill_rval_rixx_test();
    rill_rval_ruxx_test ();
    rill_rval_rfxx_test ();
    rill_rval_rbuf_test ();
    // rill_rval_rvec_test ();
    // rill_rval_rmap_test ();
}

void rill_test_all () {
    rill_rval_test();
}

int main ( int argc, char ** argv ) {

    printf( "--------------------- rill test begin\n" );

    rtest_begin( "sanity" ); {
        insist( 1 + 1 == 2 );
    } rtest_end();

    rill_test_all();

    if ( __rill_all_tests_passing ) {
        printf( "--------------------- rill test end, pass\n" );
        return 0;
    } else {
        printf( "--------------------- rill test end, fail\n\n" );
        return 1;
    }

}

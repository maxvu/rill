#include <stdio.h>
#include "test.h"

int main ( int argc, char ** argv ) {
    #ifdef RILL_RUN_TESTS
        if ( rill_run_tests() ) {
            printf( "all tests pass\n" );
            return 0;
        } else {
            printf( "test failure\n" );
            return 9;
        }
    #else
        printf( "ok\n" );
        return 0;
    #endif
}

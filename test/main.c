#include "test.h"

#include <stdio.h>

int main ( int argc, char ** argv ) {

    rtest_init();

    RTEST_BEGIN("sanity") {
        INSIST( 1 + 1 == 3 );
        INSIST( 1 + 1 == 2 );
    } RTEST_END;

    rill_test_all();
    
    return 0;

}

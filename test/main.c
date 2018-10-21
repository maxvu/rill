#include <stdio.h>

#include "rtest.h"
#include "tests.h"

void rtest_debug ( void * data ) {

}

int main ( int argc, char ** argv ) {

    test_sanity();
    test_rval();

    printf(
        "%u / %u assertions passed\n",
        ___assertions_passed,
        ___assertions_count
    );

    printf(
        "%u / %u tests passed\n",
        ___tests_passed,
        ___tests_count
    );

    return 0;
}

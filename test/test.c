#include "test.h"

int n_run = 0;
int n_passed = 0;

void test_all () {
    test_rval();
}

int main ( int argc, char ** argv ) {

    test_all();

    printf( "%d tests run\n", n_run );
    printf( "%d tests passed\n", n_passed );

    return n_run == n_passed;

}

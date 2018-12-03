#include <stdio.h>

#include "environment.h"

#include "rill_test.h"
#include "rval.test.h"

void test_all () {
    test_rval();
}

int main ( int argc, char ** argv ) {
    ___rtest_init();
    test_all();
    return ___rtest_num_conditions() != ___rtest_num_conditions_passing();
}

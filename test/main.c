#include <stdio.h>

#include "environment.h"
#include "rval/rbuf.h"

#include "rill_test.h"

int main ( int argc, char ** argv ) {
    ___rtest_init();
    printf( "test OK\n" );
    return 0;
}

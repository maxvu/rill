#include "rtest/rtest.h"

#include "rerr.h"
#include "rfxx.h"
#include "rixx.h"
#include "ruxx.h"
#include "rstr.h"
#include "rval.h"
#include "rvec.h"
#include "rmap.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main ( int argc, char ** argv ) {

    RTEST_INIT;
    
    RTEST( "sanity" ) {
        ASSERT( 1 + 1 == 2 );
    } RTEST_END;
    
    clock_t begin = clock();
    
    #include "rval.test.inc"
    #include "rixx.test.inc"
    #include "ruxx.test.inc"
    #include "rfxx.test.inc"
    #include "rstr.test.inc"
    #include "rvec.test.inc"
    #include "rmap.test.inc"
    
    clock_t end = clock();
    
    printf(
        "%lu / %lu assertions passed in %fs\n",
        RTEST_NUM_PASSED,
        RTEST_NUM_TESTS,
        ( end - begin ) / ( double ) CLOCKS_PER_SEC
    );
    
    return RTEST_OK ? 0 : 1;

}
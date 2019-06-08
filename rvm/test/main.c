#include "rtest/rtest.h"

#include "rfxx.h"
#include "rixx.h"
#include "ruxx.h"
#include "rstr.h"
#include "rval.h"
#include "rvec.h"
#include "rmap.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

int main ( int argc, char ** argv ) {

    RTEST_INIT;

    RTEST( "sanity" ) {
        ASSERT( 1 + 1 == 3 );
    } RTEST_END;
    
    RTEST( "rval / rnil / is falsy" ) {
        rval nil = rnil();
        ASSERT( !rval_truthy( &nil ) );
    } RTEST_END;
    
    RTEST( "rval / ruxx / access" ) {
        rval u = ruxxq( 12 );
        ASSERT( ruxx_get( &u ) == 12 );
    } RTEST_END;
    
    RTEST( "rval / rixx / access" ) {
        rval u = rixxq( 37 );
        ASSERT( rixx_get( &u ) == 37 );
    } RTEST_END;
    
    RTEST( "rval / rifx / access" ) {
        rval u = rfxxq( 95.0 );
        ASSERT( rfxx_get( &u ) - 95.0 < 0.001 );
    } RTEST_END;
    
    return RTEST_OK ? 0 : 1;

}
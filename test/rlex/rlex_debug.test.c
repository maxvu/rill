#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rval/dump.h"
#include "rval/rvec.h"
#include "test/test.h"

#include <stdio.h>

void rill_test_rlex_debug () {

    RTEST_BEGIN( "rval / buf / initialization" )  {
        RVal buf = rbuf();
        INSIST( rbuf_strcpy( &buf, "   : some-word 1 1 + ;" ) );

        RVal result = rvec();
        INSIST( rlex( &result, &buf ) );
        rval_dump( &result );
        printf( "\n" );
        printf( "CODE: %lu\n", rerr_get() );

    } RTEST_END;

}

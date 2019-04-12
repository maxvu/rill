#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rval/dump.h"
#include "rval/rvec.h"
#include "test/test.h"

#include <stdio.h>

void rill_test_rlex_debug () {

    RTEST_BEGIN( "rlex / debug" )  {
        RVal buf = rbuf();
        INSIST( rbuf_strcpy( &buf, "   some-word    " ) );
        rlex_dump( &buf );
        printf( "\n" );
    } RTEST_END;

}

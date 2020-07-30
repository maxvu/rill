#include <stdio.h>
#include "rill_test.h"

int main ( int argc, char ** argv ) {
    rts * ts = rts_create();
    if ( !ts ) {
        fprintf( stderr, "failed creating test suite\n" );
        return 4;
    }

    #define RILL_TEST_BEGIN( name ) rts_begin_test( ts, name );
    #define INSIST( cond )          rts_assert( ts, cond, #cond );
    #define RILL_TEST_END           rts_report_test( ts ); rts_end_test( ts );

    #include "000-sanity.c"

    rts_report_all( ts );
    return !rts_successful( ts );
}

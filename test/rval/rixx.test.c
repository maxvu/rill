#include "rill_test.h"
#include "rval/rnil.h"
#include "rval/rixx.h"

void rill_rval_rixx_test () {

    rtest_begin( "rixx / get and set" ); {
        RVal x = rnil();
        rixx_set( &x, 123 );
        insist( rixx_get( &x ) == 123 );
        rixx_set( &x, 321 );
        insist( rixx_get( &x ) == 321 );
    } rtest_end();

}

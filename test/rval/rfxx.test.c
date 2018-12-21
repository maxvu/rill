#include "rill_test.h"
#include "rval/rnil.h"
#include "rval/rfxx.h"

void rill_rval_rfxx_test () {

    rtest_begin( "rfxx / get and set" ); {
        RVal a = rfxx( 1.0 );
        RVal b = rfxx( 2.0 );
        RVal c = rfxx( rfxx_get( &a ) + rfxx_get( &b ) );
        insist( rfxx_get( &c ) - 3.0 < 0.0001 );
        insist( rval_type( &c ) == RVT_FXX );
    } rtest_end();

}

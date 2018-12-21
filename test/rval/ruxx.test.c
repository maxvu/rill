#include "rill_test.h"
#include "rval/rnil.h"
#include "rval/ruxx.h"

void rill_rval_ruxx_test () {

    rtest_begin( "ruxx / get and set" ); {
        RVal x = rnil();
        ruxx_set( &x, 22002200 );
        insist( ruxx_get( &x ) == 22002200 );
        ruxx_set( &x, 123 );
        insist( ruxx_get( &x ) == 123 );
        insist( rval_type( &x ) == RVT_UXX );
    } rtest_end();

}

#include "rill_test.h"
#include "rval/rnil.h"
#include "rval/rbuf.h"

void rill_rval_rbuf_test () {

    rtest_begin( "rbuf / get and set" ); {
        RVal a = rbuf( 10 );
        RVal b = rbuf( 10 );

        insist( rval_type( &a ) == RVT_BUF );
        insist( rval_type( &b ) == RVT_BUF );

        insist( rbuf_strcpy( &a, "hello" ) );
        insist( rbuf_strcat( &b, "hello" ) );

        rval_release( &a );
        rval_release( &b );
    } rtest_end();

}

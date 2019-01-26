#include "test.h"

void rill_test_rval_rmap () {

    RTEST_BEGIN( "rval / map / set, get, unset" )  {
        RVal map = rmap();
        RVal k = rbuf();
        RVal v = rixx( 0 );

        const char * numbers[17] = {
            "one",
            "two",
            "three",
            "four",
            "five",
            "six",
            "seven",
            "eight",
            "nine",
            "ten",
            "eleven",
            "twelve",
            "thirteen",
            "fourteen",
            "fifteen",
            "sixteen",
            "seventeen"
        };

        for ( size_t i = 0; i < 17; i++ ) {
            // rmap_dbgprint( &map );
            INSIST( rbuf_strcpy( &k, numbers[ i ] ) );
            rixx_set( &v, i );
            INSIST( rmap_set( &map, &k, &v ) );
        }
        // rmap_dbgprint( &map );

        rval_release( &k );
        rval_release( &map );
    } RTEST_END;

    /*
        set / get / unset
        clone
        keys
        vals
        merge
    */

}

#include "test/test.h"
#include "rval/rixx.h"
#include "rval/rval.h"
#include "rval/rvec.h"
#include "rval/rmap.h"

void rill_test_rval_rmap () {

    RTEST_BEGIN( "rval / map / set, get, unset, resize, keys, vals" )  {
        RVal map = rmap();
        RVal k = rbuf();
        RVal v = rixx( 0 );

        const char * numbers[ 17 ] = {
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

        // Insert 17 members.
        for ( size_t i = 0; i < 17; i++ ) {
            INSIST( rbuf_strcpy( &k, numbers[ i ] ) );
            rixx_set( &v, i + 1 );
            INSIST( rmap_set( &map, &k, &v ) );
        }

        // Retrieve 17 members.
        for ( size_t i = 0; i < 17; i++ ) {
            INSIST( rbuf_strcpy( &k, numbers[ i ] ) );
            rixx_set( &v, rixx_get( rmap_get( &map, &k ) ) );
            INSIST( rixx_get( &v ) == i + 1 );
        }

        // Survives resizing.
        INSIST( rmap_reserve( &map, 50 ) );
        INSIST( rmap_compact( &map ) );
        for ( size_t i = 0; i < 17; i++ ) {
            INSIST( rbuf_strcpy( &k, numbers[ i ] ) );
            rixx_set( &v, rixx_get( rmap_get( &map, &k ) ) );
            INSIST( rixx_get( &v ) == i + 1 );
        }
        INSIST( rmap_size( &map ) == 17 );

        {
            RVal keys = rnil();
            INSIST( rmap_keys( &keys, &map ) );
            INSIST( rvec_len( &keys ) == 17 );
            rval_release( &keys );
        }

        {
            RVal vals = rnil();
            INSIST( rmap_vals( &vals, &map ) );
            INSIST( rvec_len( &vals ) == 17 );
            rval_release( &vals );
        }

        // Unset a single member.
        INSIST( rbuf_strcpy( &k, "three" ) );
        INSIST( rmap_unset( &map, &k ) );
        INSIST( rmap_get( &map, &k ) == NULL );
        INSIST( rmap_size( &map ) == 16 );

        INSIST( rmap_clear( &map ) );
        INSIST( rmap_size( &map ) == 0 );

        rval_release( &k );
        rval_release( &map );
    } RTEST_END;

    /*
        clone
        merge
    */

}

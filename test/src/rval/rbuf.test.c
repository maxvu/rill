#include <string.h>

#include "rill_test.h"

#include "rval/rbuf.h"

void test_rval_rbuf () {

    TEST_BEGIN( "rbuf / init" ) {
        RBuf * buf = rbuf_create( 10 );
        INSIST( rbuf_len( buf ) == 0 );
        INSIST( rbuf_unique( buf ) );
        rbuf_destroy( buf );
    } TEST_END

    TEST_BEGIN( "rbuf / ops" ) {
        RBuf * a = rbuf_create( 10 );
        RBuf * b = rbuf_create( 10 );

        INSIST( rbuf_reserve( a, 5 ) );

        INSIST( rbuf_cpyc( a, "hello" ) );
        INSIST( rbuf_catc( b, " world!" ) );
        INSIST( rbuf_len( a ) == 5 );
        INSIST( rbuf_len( b ) == 7 );
        INSIST( rbuf_cmp( a, b ) != 0 );

        INSIST( rbuf_cat( a, b ) );
        INSIST( rbuf_cmpc( a, "hello world!" ) == 0 );
        INSIST( strcmp( "hello world!", rbuf_get( a ) ) == 0 );

        rbuf_clear( a );
        INSIST( rbuf_len( a ) == 0 );

        INSIST( rbuf_cpy( a, b ) );
        INSIST( rbuf_cmp( a, b ) == 0 );

        rbuf_ref( a );
        rbuf_deref( a );

        rbuf_deref( a );
        rbuf_deref( b );
    } TEST_END

    TEST_BEGIN( "rbuf / resizing" ) {
        RBuf * a = rbuf_create( 10 );

        const char * msg = "0123456789";

        for ( size_t i = 0; i < 100; i++ ) {
            INSIST( rbuf_catc( a, msg ) );
        }
        INSIST( rbuf_len( a ) == 1000 );

        INSIST( rbuf_compact( a ) );
        INSIST( rbuf_len( a ) == 1000 );

        rbuf_clear( a );
        rbuf_clear( a );
        INSIST( rbuf_len( a ) == 0 );
        INSIST( rbuf_compact( a ) );

        rbuf_destroy( a );
    } TEST_END

}

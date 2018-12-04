#include <string.h>

#include "rill_test.h"

#include "rval/rbuf.h"

void test_rval_rbuf () {

    TEST_BEGIN( "rbuf / init" ) {
        RBuf * buf = __rbuf_create( 10 );
        INSIST( __rbuf_len( buf ) == 0 );
        INSIST( __rbuf_unique( buf ) );
        __rbuf_destroy( buf );
    } TEST_END

    TEST_BEGIN( "rbuf / ops" ) {
        RBuf * a = __rbuf_create( 10 );
        RBuf * b = __rbuf_create( 10 );

        INSIST( __rbuf_reserve( a, 5 ) );

        INSIST( __rbuf_cpyc( a, "hello" ) );
        INSIST( __rbuf_catc( b, " world!" ) );
        INSIST( __rbuf_len( a ) == 5 );
        INSIST( __rbuf_len( b ) == 7 );
        INSIST( __rbuf_cmp( a, b ) != 0 );

        INSIST( __rbuf_cat( a, b ) );
        INSIST( __rbuf_cmpc( a, "hello world!" ) == 0 );
        INSIST( strcmp( "hello world!", __rbuf_get( a ) ) == 0 );

        __rbuf_clear( a );
        INSIST( __rbuf_len( a ) == 0 );

        INSIST( __rbuf_cpy( a, b ) );
        INSIST( __rbuf_cmp( a, b ) == 0 );

        __rbuf_lease( a );
        __rbuf_release( a );

        __rbuf_release( a );
        __rbuf_release( b );
    } TEST_END

    TEST_BEGIN( "rbuf / resizing" ) {
        RBuf * a = __rbuf_create( 10 );

        const char * msg = "0123456789";

        for ( size_t i = 0; i < 100; i++ ) {
            INSIST( __rbuf_catc( a, msg ) );
        }
        INSIST( __rbuf_len( a ) == 1000 );

        INSIST( __rbuf_compact( a ) );
        INSIST( __rbuf_len( a ) == 1000 );

        __rbuf_clear( a );
        __rbuf_clear( a );
        INSIST( __rbuf_len( a ) == 0 );
        INSIST( __rbuf_compact( a ) );

        __rbuf_destroy( a );
    } TEST_END

}

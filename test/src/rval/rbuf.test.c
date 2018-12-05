#include <string.h>

#include "rill_test.h"

#include "rval/rbuf.h"

void test_rval_rbuf () {

    TEST_BEGIN( "rval / rbuf / newly-initialized rbuf has length 0 and refcount 1" ) {
        RBuf * a = __rbuf_create( 10 );
        INSIST( a != NULL );
        INSIST( __rbuf_len( a ) == 0 );
        INSIST( __rbuf_unique( a ) );
        __rbuf_destroy( a );
    } TEST_END;

    TEST_BEGIN( "rval / rbuf / lease increments count, release decrements" ) {
        RBuf * a = __rbuf_create( 10 );
        INSIST( a != NULL );
        INSIST( __rbuf_unique( a ) );
        __rbuf_lease( a );
        INSIST( !__rbuf_unique( a ) );
        __rbuf_release( a );
        INSIST( __rbuf_unique( a ) );
        __rbuf_release( a ); // destroyed.
    } TEST_END;

    TEST_BEGIN( "rval / rbuf / reserve() and compact() don't clobber buffer" ) {
        RBuf * a = __rbuf_create( 500 );
        const char * msg = "0123456789";
        char * cstr = malloc( sizeof( char ) * 10 * 100 + 1 );
        strcpy( cstr, "" );

        INSIST( a != NULL );
        for ( size_t i = 0; i < 100; i++ ) {
            INSIST( __rbuf_catc( a, msg ) );
            strcat( cstr, msg );
        }
        INSIST( __rbuf_len( a ) == 1000 );
        INSIST( strcmp( cstr, __rbuf_get( a ) ) == 0 );

        INSIST( __rbuf_reserve( a, 1500 ) );
        INSIST( __rbuf_len( a ) == 1000 );
        INSIST( strcmp( cstr, __rbuf_get( a ) ) == 0 );

        INSIST( __rbuf_compact( a ) );
        INSIST( __rbuf_len( a ) == 1000 );
        INSIST( strcmp( cstr, __rbuf_get( a ) ) == 0 );

        free( cstr );
        __rbuf_destroy( a );
    } TEST_END;

    TEST_BEGIN( "rval / rbuf / _cpy works" ) {
        RBuf * a = __rbuf_create( 10 );
        RBuf * b = __rbuf_create( 10 );

        INSIST( __rbuf_cpyc( a, "hello" ) );
        INSIST( __rbuf_cpy( b, a ) );

        INSIST( __rbuf_len( a ) == 5 );
        INSIST( __rbuf_len( b ) == 5 );
        INSIST( __rbuf_cmp( a, b ) == 0 );

        __rbuf_destroy( a );
        __rbuf_destroy( b );
    } TEST_END;

    TEST_BEGIN( "rval / rbuf / _cat works" ) {
        RBuf * a = __rbuf_create( 10 );
        RBuf * b = __rbuf_create( 10 );

        INSIST( __rbuf_cpyc( a, "hello" ) );
        INSIST( __rbuf_cpyc( b, " world!" ) );
        INSIST( __rbuf_cat( a, b ) );

        INSIST( __rbuf_cmpc( a, "hello world!" ) == 0 );

        __rbuf_destroy( a );
        __rbuf_destroy( b );
    } TEST_END;

    TEST_BEGIN( "rval / rbuf / _cpy()'ing a zero-length buf doesn't modify" ) {
        RBuf * a = __rbuf_create( 10 );
        RBuf * b = __rbuf_create( 10 );

        INSIST( __rbuf_cpyc( a, "hello" ) );
        INSIST( __rbuf_cpyc( b, "" ) );
        INSIST( __rbuf_cat( a, b ) );

        INSIST( __rbuf_cmpc( a, "hello" ) == 0 );

        __rbuf_destroy( a );
        __rbuf_destroy( b );
    } TEST_END;

    TEST_BEGIN( "rval / rbuf / _cpyc()'ing a zero-length c-string doesn't modify" ) {
        RBuf * a = __rbuf_create( 10 );

        INSIST( __rbuf_cpyc( a, "hello" ) );
        INSIST( __rbuf_catc( a, "" ) );

        INSIST( __rbuf_cmpc( a, "hello" ) == 0 );

        __rbuf_destroy( a );
    } TEST_END;

    TEST_BEGIN( "rval / rbuf / _cmp() works" ) {
        RBuf * a = __rbuf_create( 10 );
        RBuf * b = __rbuf_create( 10 );

        INSIST( __rbuf_cpyc( a, "hello" ) );
        INSIST( __rbuf_cpyc( b, "" ) );
        INSIST( __rbuf_cat( a, b ) );
        INSIST( __rbuf_cmp( a, b ) > 0 );

        INSIST( __rbuf_cpyc( b, "h" ) );
        INSIST( __rbuf_cmp( a, b ) > 0 );

        INSIST( __rbuf_cpyc( b, "hello" ) );
        int xx = __rbuf_cmpc( a, b );
        INSIST( __rbuf_cmp( a, b ) == 0 );

        __rbuf_destroy( a );
        __rbuf_destroy( b );
    } TEST_END;

    TEST_BEGIN( "rval / rbuf / _clear() works" ) {
        RBuf * a = __rbuf_create( 10 );

        INSIST( __rbuf_cpyc( a, "hello" ) );
        __rbuf_clear( a );
        INSIST( __rbuf_len( a ) == 0 );
        INSIST( __rbuf_cmpc( a, "" ) == 0 );

        __rbuf_destroy( a );
    } TEST_END;

}

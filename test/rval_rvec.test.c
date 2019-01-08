#include "test.h"

void rill_test_rval_rvec () {

    RTEST_BEGIN( "rval / vec / push, pop, get, set" )  {
        RVal vec = rvec();
        RVal item = rnil();
        INSIST( rvec_len( &vec ) == 0 );
        for ( size_t i = 0; i < 10; i++ ) {
            item = rixx( i );
            INSIST( rvec_push( &vec, &item ) );
        }
        INSIST( rvec_len( &vec ) == 10 );
        INSIST( rixx_get( rvec_get( &vec, 7 ) ) == 7 );
        rixx_set( rvec_get( &vec, 7 ), 9 );
        INSIST( rixx_get( rvec_get( &vec, 7 ) ) == 9 );
        INSIST( rvec_clear( &vec ) );

        INSIST( !rvec_pop( &vec ) );
        rval_release( &vec );
    } RTEST_END;

    RTEST_BEGIN( "rval / vec / fill, contain recursive vals" )  {
        RVal vec = rvec();
        RVal subvec = rvec();
        RVal item = rnil();
        INSIST( rvec_push( &subvec, &item ) );
        INSIST( rvec_fill( &vec, &subvec, 10 ) );
        INSIST( rvec_len( &vec ) == 10 );

        rval_release( &vec );
        rval_release( &subvec );
    } RTEST_END;

    RTEST_BEGIN( "rval / vec / copy" )  {
        RVal vec = rvec();

        RVal item = rnil();
        for ( size_t i = 0; i < 10; i++ ) {
            item = rixx( i );
            INSIST( rvec_push( &vec, &item ) );
        }

        RVal vec2 = rnil();
        INSIST( rval_copy( &vec2, &vec ) );
        INSIST( rvec_get( &vec, 5 ) == rvec_get( &vec2, 5 ) );

        rval_release( &vec );
        rval_release( &vec2 );
    } RTEST_END;

    RTEST_BEGIN( "rval / vec / clone" )  {
        RVal vec = rvec();

        RVal item = rnil();
        for ( size_t i = 0; i < 10; i++ ) {
            item = rixx( i );
            INSIST( rvec_push( &vec, &item ) );
        }

        RVal vec2 = rnil();
        INSIST( rvec_clone( &vec2, &vec ) );
        INSIST( rvec_get( &vec, 5 ) != rvec_get( &vec2, 5 ) );
        INSIST( rixx_get( rvec_get( &vec, 5 ) ) == 5 );

        rval_release( &vec );
        rval_release( &vec2 );
    } RTEST_END;

    RTEST_BEGIN( "rval / vec / reverse" )  {
        RVal vec = rvec();
        RVal item = rnil();

        item = rixx( 1 );
        INSIST( rvec_push( &vec, &item ) );
        item = rixx( 2 );
        INSIST( rvec_push( &vec, &item ) );
        item = rixx( 3 );
        INSIST( rvec_push( &vec, &item ) );

        // odd count
        INSIST( rvec_reverse( &vec ) );
        INSIST( rvec_len( &vec ) == 3 );
        INSIST( rixx_get( rvec_get( &vec, 0 ) ) == 3 );
        INSIST( rixx_get( rvec_get( &vec, 1 ) ) == 2 );
        INSIST( rixx_get( rvec_get( &vec, 2 ) ) == 1 );

        INSIST( rvec_reverse( &vec ) );
        item = rixx( 4 );
        INSIST( rvec_push( &vec, &item ) );

        // even count
        INSIST( rvec_reverse( &vec ) );
        INSIST( rixx_get( rvec_get( &vec, 0 ) ) == 4 );
        INSIST( rixx_get( rvec_get( &vec, 1 ) ) == 3 );
        INSIST( rixx_get( rvec_get( &vec, 2 ) ) == 2 );
        INSIST( rixx_get( rvec_get( &vec, 3 ) ) == 1 );

        rval_release( &vec );
    } RTEST_END;

    RTEST_BEGIN( "rval / vec / survives resizing" )  {
        RVal vec = rnil();
        RVal item = rnil();
        INSIST( rvec_init( &vec, 30 ) );

        for ( size_t i = 0; i < 50; i++ ) {
            ruxx_set( &item, i );
            INSIST( rvec_push( &vec, &item ) );
        }
        INSIST( rvec_len( &vec ) == 50 );
        INSIST( ruxx_get( rvec_get( &vec, 47 ) ) == 47 );

        INSIST( rvec_reserve( &vec, 100 ) );
        INSIST( rvec_compact( &vec ) );

        INSIST( rvec_len( &vec ) == 50 );
        INSIST( ruxx_get( rvec_get( &vec, 46 ) ) == 46 );

        rval_release( &vec );
    } RTEST_END;


    /*

        can contain another vec (can release()'ing outside)
        concat (with self)
        insert into self
        clear
        iteration
    */

}

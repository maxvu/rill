#include "test.h"
#include "rval.h"

void test_rval_numerics () {
    RILL_TEST( "rval / can get and set uxx, ixx and fxx", ({
        RVal a, b, c;
        rval_fzero( &a );
        rval_fzero( &b );
        rval_fzero( &c );

        ruxx_set( &a, 20 );
        rixx_set( &b, -30 );
        rfxx_set(
            &c,
            (
                ( double ) ruxx_get( &a ) +
                ( double ) rixx_get( &b )
            )
        );
        INSIST( rfxx_get( &c ) - -10.0 < 0.0001 );
        INSIST( rval_type( &a ) == RVT_UXX );
        INSIST( rval_type( &b ) == RVT_IXX );
        INSIST( rval_type( &c ) == RVT_FXX );

        RVal d, e, f;
        rval_fzero( &d );
        rval_fzero( &e );
        rval_fzero( &f );

        rval_copy( &d, &a );
        rval_copy( &e, &b );
        rval_clone( &f, &c );
        INSIST( rval_type( &d ) == RVT_UXX );
        INSIST( rval_type( &e ) == RVT_IXX );
        INSIST( rval_type( &f ) == RVT_FXX );
    }) );
}

void test_rval_str () {
    RILL_TEST( "rval / string ops", ({
        RVal a, b, c;
        rval_fzero( &a );
        rval_fzero( &b );
        rval_fzero( &c );

        // Init 'a'.
        rstr_init( &a, 16 );
        INSIST( rval_type( &a ) == RVT_STR );
        INSIST( rstr_len( &a ) == 0 );
        INSIST( strcmp( "", rstr_get( &a ) ) == 0 );

        // Cat c-strings to it. (_setc, _catc, _cmpc)
        rstr_setc( &a, "hel", 3 );
        rstr_catc( &a, "lo ", 3 );
        INSIST( rstr_len( &a ) == 6 );
        INSIST( rstr_cmpc( &a, "hello ", 6 ) == 0 );
        INSIST( rstr_cmpc( &a, "hello !", 7 ) < 0 );

        // Init 'b' and cat it to 'a'. (_cat)
        rstr_setc( &b, "world", 5 );
        rstr_cat( &a, &b );
        INSIST( rstr_len( &a ) == 11 );
        INSIST( strcmp( "hello world", rstr_get( &a ) ) == 0 );

        // (set, cpm)
        rstr_copy( &b, &a );
        INSIST( rstr_cmp( &a, &b ) == 0 );

        // _init()'ing a string reserve()'s
        INSIST( rstr_init( &a, 100 ) );
        INSIST( rstr_cmp( &a, &b ) == 0 );

        // cat() and catc()'ing init() non-strings.
        INSIST( rstr_catc( &c, "hello", 5 ) );
        INSIST( rstr_cmpc( &c, "hello", 5 ) == 0 );

        // (clear)
        rstr_clear( &a );
        rstr_clear( &b );
        INSIST( rstr_cmp( &a, &b ) == 0 );

        rstr_release( &a );
        rstr_release( &b );
        rstr_release( &c );
        INSIST( rval_type( &a ) == RVT_NIL );
    }) );

    RILL_TEST( "rval / string resizing", ({
        RVal a, b;

        // Build up a long message. Make sure it expands.
        const char * msg = "10000 20000 30000 40000 50000 ";
        INSIST( rstr_init( &a, 100 ) );
        for ( size_t i = 0; i < 100; i++ ) {
            rstr_catc( &a, msg, 30 );
        }

        // Make sure it's intact.
        INSIST( rstr_len( &a ) == 30 * 100 );
        const char * offset = rstr_get( &a ) + sizeof( char ) * 30 * 70;
        INSIST( memcmp( msg, offset, 30 ) == 0 );

        // Contract it again.
        rstr_setc( &a, "hello world", 11 );
        INSIST( rstr_compact( &a ) );
        INSIST( rstr_cmpc( &a, "hello world", 11 ) == 0 );

        // Expand it again.
        INSIST( rstr_reserve( &a, 100 ) );
        INSIST( rstr_cmpc( &a, "hello world", 11 ) == 0 );
        rstr_release( &a );
    }) );
}

void test_rval_vec () {
    RILL_TEST( "rval / vec ops", ({
        RVal a;
        RVal v1;
        rval_fzero( &a );
        rval_fzero( &v1 );

        // push() ten items.
        INSIST( rvec_init( &v1, 10 ) );
        for ( size_t i = 1; i <= 10; i++ ) {
            ruxx_set( &a, i );
            INSIST( rvec_push( &v1, &a ) );
        }

        // There are ten and we can get one.
        INSIST( rvec_len( &v1 ) == 10 );
        INSIST( ruxx_get( rvec_get( &v1, 5 ) ) == 6 );

        // OOB access is null.
        INSIST( rvec_get( &v1, 99 ) == NULL );

        rvec_release( &v1 );
    }) );

    RILL_TEST( "rval / concat", ({
        RVal a;
        RVal v1, v2;
        rval_fzero( &a );
        rval_fzero( &v1 );
        rval_fzero( &v2 );

        // Push ten items to a.
        for ( size_t i = 1; i <= 5; i++ ) {
            ruxx_set( &a, i );
            INSIST( rvec_push( &v1, &a ) );
        }

        // // Copy them to the other vec.
        INSIST( rvec_concat( &v2, &v1 ) );
        INSIST( rvec_len( &v2 ) == 5 );

        // // Concat it back to the original.
        INSIST( rvec_concat( &v1, &v2 ) );
        INSIST( rvec_len( &v1 ) == 10 );

        rval_dump( &v1 );
        rval_dump( &v2 );

        hiya: 1;
        rval_release( &v1 );
        rval_release( &v2 );
    }) );

    // RILL_TEST( "rval / fill", ({
    //     RVal a;
    //     RVal v1;
    //     rval_fzero( &a );
    //     rval_fzero( &v1 );
    //     ruxx_set( &a, 10 );
    //
    //     INSIST( rvec_init( &v1, 10 ) );
    //     INSIST( rvec_fill( &v1, 10, &a ) );
    //     INSIST( rvec_len( &v1 ) == 10 );
    //
    //     ruxx_set( &a, 1 );
    //     INSIST( rvec_set( &v1, 6, &a ) );
    //
    //     size_t sum = 0;
    //     for ( size_t i = 0; i < 10; i++ ) {
    //         RVal * item = rvec_get( &v1, i );
    //         sum += ruxx_get( item );
    //     }
    //     INSIST( sum == 91 );
    //     rvec_release( &v1 );
    // }) );

    RILL_TEST( "rval / shared access", ({

        RVal outer, inner;


    }) );
    //
    // RILL_TEST( "vec resizing", ({
    //     INSIST( 0 );
    // }) );
    //
    // RILL_TEST( "vec edge cases", ({
    //     INSIST( 0 );
    // }) );
}

void test_rval_map () {
//     RILL_TEST( "map ops", ({
//         INSIST( 0 );
//     }) );
//
//     RILL_TEST( "map resizing", ({
//         INSIST( 0 );
//     }) );
//
//     RILL_TEST( "vec edge cases", ({
//         INSIST( 0 );
//     }) );
}

void test_rval () {
    test_rval_numerics ();
    test_rval_str ();
    test_rval_vec ();
    test_rval_map ();
}

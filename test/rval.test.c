#include "test.h"
#include "rval.h"

void test_rval_numerics () {
    RILL_TEST( "get+set uxx, ixx and fxx", ({
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
    RILL_TEST( "string ops", ({
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
        INSIST( rstr_cmpc( &a, "hello !", 7 ) == -1 );

        // Init 'b' and cat it to 'a'. (_cat)
        rstr_setc( &b, "world", 5 );
        rstr_cat( &a, &b );
        INSIST( rstr_len( &a ) == 11 );
        INSIST( strcmp( "hello world", rstr_get( &a ) ) == 0 );



        rstr_release( &a );
        rstr_release( &b );
    }) );

    RILL_TEST( "string resizing", ({

    }) );

    RILL_TEST( "string edge cases", ({

    }) );
}

void test_rval_vec () {
    RILL_TEST( "vec ops", ({

    }) );

    RILL_TEST( "vec resizing", ({

    }) );

    RILL_TEST( "vec edge cases", ({

    }) );
}

void test_rval_map () {
    RILL_TEST( "vec ops", ({

    }) );

    RILL_TEST( "map resizing", ({

    }) );

    RILL_TEST( "vec edge cases", ({

    }) );
}

void test_rval () {
    test_rval_numerics ();
    test_rval_str ();
    test_rval_vec ();
    test_rval_map ();
}

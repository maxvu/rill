#include "test.h"

#include "rval.h"

void test_rval () {

    {

        RVal a, b;
        rval_uxx_init( &a );
        rval_uxx_init( &b );
        rval_uxx_set( &a, 1 );
        rval_uxx_copy( &b, &a );
        rval_uxx_set( &a, 2 );
        insist(
            rval_uxx_get( &a ) + rval_uxx_get( &b ) == 3,
            "1u + 2u == 3u"
        );

    }

    {

        RVal a, b;
        rval_ixx_init( &a );
        rval_ixx_init( &b );

        rval_ixx_set( &a, -2 );
        rval_ixx_copy( &b, &a );
        rval_ixx_set( &a, 8 );

        insist(
            rval_ixx_get( &a ) + rval_ixx_get( &b ) == 6,
            "-2i + 8i = 6i"
        );

    }

    {

        RVal a, b;
        rval_fxx_init( &a );
        rval_fxx_init( &b );

        rval_fxx_set( &a, 1.5 );
        rval_fxx_copy( &b, &a );
        rval_fxx_set( &a, -1.5 );

        insist(
            rval_fxx_get( &a ) - rval_fxx_get( &b ) < 0.01,
            "-1.5 + 1.5 ~= 0.0"
        );

    }

    {
        RVal a, b;
        rval_str_init( &a, 16 );
        rval_str_copy( &b, &a );

        rval_str_setc( &b, "Hello" );
        rval_str_cat( &a, &b );
        rval_str_clear( &b );
        rval_str_catc( &b, ", World!" );
        rval_str_cat( &a, &b );

        insist(
            rval_str_cmpc( &a, "Hello, World!" ) == 0,
            "'Hello' + ', World!' == 'Hello, World!'"
        );
        rval_str_release( &a );
        rval_str_release( &b );
    }

    {

        RVal a, b, c;
        rval_str_init( &a, 16 );
        rval_str_setc( &a, "test" );

        rval_str_copy( &b, &a );
        rval_str_copy( &c, &a );

        insist(
            ( a.str == b.str ) &&
            ( b.str == c.str ) &&
            a.str->ref == 3,
            "can ref() strings"
        );

        rval_str_setc( &b, "test2" );
        rval_str_setc( &c, "test3" );

        rval_str_release( &a );
        rval_str_release( &b );
        rval_str_release( &c );

    }

}

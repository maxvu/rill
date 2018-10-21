#include "rtest.h"

#include "rval/rval.h"
#include "rval/ruxx.h"
#include "rval/rixx.h"
#include "rval/rfxx.h"
#include "rval/rstr.h"

void test_rval () {

    test("ruxx / rixx / rfxx type set", ({

        RVal a, b, c;
        rval_fzero( &a );
        rval_fzero( &b );
        rval_fzero( &c );

        ruxx_set( &a, 11 );
        ruxx_set( &b, 22 );
        ruxx_set( &c, ruxx_get( &a ) + ruxx_get( &b ) );

        insist( ruxx_get( &c ) == 33 );

        rfxx_set( &a, 15.0 );
        ruxx_set( &b, 100u );
        rixx_set( &c, rfxx_get( &a ) + ruxx_get( &b ) );

        insist( rixx_get( &c ) == 115 );

    }) );

    test("rstr init(), cat(), cmp()", {
        RVal a;
        rval_fzero( &a );
        rstr_init( &a, 20 );
        rstr_setc( &a, "hello", 5 );
        rstr_catc( &a, " world", 6 );
        insist( rstr_len( &a ) == 11 );
        insist( rstr_cmpc( &a, "hello world", 11 ) == 0 );

        RVal b;
        rval_fzero( &b );
        rstr_init( &b, 11 );
        rstr_set( &b, &a );
        insist( rstr_len( &b ) == 11 );
        insist( rstr_cmp( &a, &b ) == 0 );

        rstr_catc( &b, "!!", 2 );
        insist( rstr_cmp( &a, &b ) == -1 );

        rstr_release( &a );
        rstr_release( &b );
    });

}

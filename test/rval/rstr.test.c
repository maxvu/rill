#include "test.h"
#include "rval/rstr.h"
#include "rval/rval.h"

void test_rval_rstr () {

    test("can init(), cat(), cmp()", {
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

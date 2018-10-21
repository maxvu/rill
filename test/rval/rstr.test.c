#include "test.h"
#include "rval/rstr.h"
#include "rval/rval.h"

void test_rval_rstr () {

    test("can init(), cat(), cmp()", {
        RVal a;
        rval_fzero( &a );
        rstr_init( &a, 20 );
        rstr_setc( &a, "hello", 5 );

        insist( rstr_cmpc( &a, "hello", 5 ) == 0 );
        insist( rstr_cmpc( &a, "goodbye", 7 ) == 1 );
    });

}

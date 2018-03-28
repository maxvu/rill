#include "test.h"

#include "rstr.h"

void test_rstr () {

    RStr * a = rstr_create();
    RStr * b = rstr_create();
    assert( rstr_len( a ) == 0, "new rstrs are empty" );

    assert( rstr_cmp( a, b ) == 0, "empty rstrs are equals" );

    rstr_reserve( a, 20 );
    assert( a->cap >= 20, "rstr reservation works" );

    rstr_set( a, b );
    assert( rstr_cmp( a, b ) == 0, "setting rstr with empty is OK" );

    rstr_set_cstr( a, "hello, " );
    rstr_set_cstr( b, "world!" );
    rstr_cat( a, b );
    assert(
        rstr_cmp_cstr( a, "hello, world!" ) == 0 &&
        rstr_cmp_cstr( b, "world!" ) == 0 &&
        rstr_cmp( a, b ) != 0,
        "rstr_cat works"
    );

    rstr_compact( a );
    assert( a->cap - 13 < 4, "rstr_compact() works" );

    rstr_destroy( a );
    rstr_destroy( b );

}

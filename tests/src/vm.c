#include "test.h"
#include "vm.h"

#include "vm/include/rstr.h"

void test_rstr () {
    test( "rstr initialization", {
        RVal msg;
        insist( rstr_init( &msg, 20 ) );
        insist( rstr_len( &msg ) == 0 );
    } );
}

void test_rval () {
    test_rstr ();
}

void test_vm () {
    test_rval();
}

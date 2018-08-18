#include "test.h"
#include "vm/include/rstr.h"

void __test_vm_rstr () {
    test( "rstr initializes properly", {
        RVal msg;
        rval_zero( &msg );
        rstr_init( &msg, 20 );

        insist( rstr_len( &msg ) == 0 );
        insist( strcmp( rstr_cstr( &msg ), "" ) == 0 );
    } )

    test( "rstr setc(), catc(), cmpc()", {
        RVal msg;
        rval_zero( &msg );
        insist( rstr_init( &msg, 20 ) );
        insist( rstr_setc( &msg, "hello " ) );
        insist( rstr_catc( &msg, "world" ) );
        insist( rstr_len( &msg ) == 11 );
        insist( rstr_cmpc( &msg, "hello world" ) == 0 );
    } )
}

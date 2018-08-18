#include "test.h"
#include "vm/include/rstr.h"

void __test_vm_rstr () {

    test( "rstr initializes properly", ({
        RVal msg;
        rval_zero( &msg );
        rstr_init( &msg, 20 );

        insist( rstr_len( &msg ) == 0 );
        insist( strcmp( rstr_cstr( &msg ), "" ) == 0 );
        rval_clear( &msg );
    }) )

    test( "rstr setc(), catc(), cmpc()", ({
        RVal msg;
        rval_zero( &msg );
        insist( rstr_init( &msg, 20 ) );
        insist( rstr_setc( &msg, "hello " ) );
        insist( rstr_catc( &msg, "world" ) );
        insist( rstr_len( &msg ) == 11 );
        insist( rstr_cmpc( &msg, "hello world" ) == 0 );
        rval_clear( &msg );
    }) )

    test( "rstr survives resizing", ({
        RVal msg;
        rval_zero( &msg );
        insist( rstr_init( &msg, 20 ) );
        insist( rstr_setc( &msg, "hello world!" ) );
        insist( rstr_reserve( &msg, 2000 ) );
        insist( msg.str->cap >= 2000 );
        insist( rstr_compact( &msg ) );
        insist( rstr_cmpc( &msg, "hello world!" ) == 0 );
        insist( rstr_len( &msg ) == 12 );
        rval_clear( &msg );
    }) )

    test( "rstr set(), cat(), cmp()", ({
        RVal a, b;
        rval_zero( &a );
        rval_zero( &b );
        insist( rstr_init( &a, 20 ) );
        insist( rstr_init( &b, 20 ) );
        insist( rstr_setc( &b, "hello" ) );
        insist( rstr_cat( &a, &b ) );
        insist( rstr_cmp( &a, &b ) == 0 );
        insist( rstr_setc( &b, " world!" ) );
        insist( rstr_cmp( &a, &b ) == 1 );
        insist( rstr_cat( &a, &b ) );
        insist( rstr_cmpc( &a, "hello world!" ) == 0 );
        rval_clear( &a );
        rval_clear( &b );
    }) )


}

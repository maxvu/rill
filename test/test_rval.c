#include "test.h"

#include <string.h>

#include "val/rval.h"
#include "val/rmap.h"
#include "val/rvec.h"
#include "val/rstr.h"

void test_rstr () {

    {
        RStr msg;
        rstr_init( &msg, 64 );
        insist( rstr_len( &msg ) == 0, "rstrs start empty" );
        rstr_release( &msg );
    }

    {
        RStr * msg = rstr_create( 64 );
        rstr_setc( msg, "hello world" );
        insist( rstr_len( msg ) == 11, "rstr setc()" );
        rstr_destroy( msg );
    }

    {
        RStr * msg = rstr_create( 64 );
        rstr_setc( msg, "hello" );
        rstr_catc( msg, " world" );
        insist( rstr_len( msg ) == 11, "rstr catc()" );
        rstr_destroy( msg );
    }

    {
        RStr * msg = rstr_create( 64 );
        rstr_setc( msg, "hello" );
        rstr_catc( msg, " world" );
        insist( rstr_cmpc( msg, "hello world" ) == 0, "rstr cmpc()" );
        insist( strcmp( rstr_cstr( msg ), "hello world" ) == 0, "rstr cstr()" );
        rstr_destroy( msg );
    }

    {
        RStr * msg1 = rstr_create( 64 );
        RStr * msg2 = rstr_create( 64 );
        rstr_setc( msg1, "hello" );
        rstr_catc( msg2, " world" );
        rstr_cat( msg1, msg2 );
        insist( rstr_cmpc( msg1, "hello world" ) == 0, "rstr cat()" );
        rstr_destroy( msg1 );
        rstr_destroy( msg2 );
    }

    {
        RStr * msg1 = rstr_create( 64 );
        RStr * msg2 = rstr_create( 64 );

        int equal_before;
        int equal_after;

        rstr_setc( msg1, "hello" );
        rstr_catc( msg2, "world" );
        equal_before = !rstr_cmp( msg1, msg2 );
        rstr_set( msg1, msg2 );
        equal_after = !rstr_cmp( msg1, msg2 );
        insist( !equal_before && equal_after == 0, "rstr cmp()" );
        rstr_destroy( msg1 );
        rstr_destroy( msg2 );
    }

    {
        RStr * msg = rstr_create( 64 );

        rstr_setc( msg, "hello world" );
        rstr_reserve( msg, 2000 );
        rstr_compact( msg );

        insist( rstr_cmpc( msg, "hello world" ) == 0, "rstr survives resize" );
        rstr_destroy( msg );
    }

    {
        RStr * msg = rstr_create( 0 );
        rstr_compact( msg );
        // no memory errors
        rstr_destroy( msg );
    }



}

void test_rvec () {

    {
        RVec * vec = rvec_create( 10 );
        insist( rvec_len( vec ) == 0, "rvecs start empty" );
        rvec_destroy( vec );
    }

    {
        RVec * vec = rvec_create( 10 );
        {
            RVal u;
            u.type = UXX;
            u.uxx = 0;
            for ( int i = 0; i < 100; i++ ) {
                rvec_push( vec, &u );
                u.uxx++;
            }
        }

        insist(
            rvec_len( vec ) == 100 &&
            rvec_get( vec, 73 )->type == UXX &&
            rvec_get( vec, 73 )->uxx == 73,
            "rvec, basic access"
        );

        rvec_reserve( vec, 900 );
        rvec_compact( vec );

        insist(
            rvec_len( vec ) == 100 &&
            rvec_get( vec, 73 )->type == UXX &&
            rvec_get( vec, 73 )->uxx == 73,
            "rvec, survives resize"
        );

        rvec_destroy( vec );
    }

}

void test_rval () {
    test_rstr();
    test_rvec();
}

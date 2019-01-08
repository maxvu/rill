#include "test.h"
#include "rval.h"

#include <string.h>

void rill_test_rval_rbuf () {

    RTEST_BEGIN( "rval / buf / initialization" )  {
        RVal buf = rbuf();
        INSIST( rbuf_len( &buf ) == 0 );
        rval_release( &buf );
    } RTEST_END;

    RTEST_BEGIN( "rval / buf / strcpy, strcat, strcmp" )  {
        RVal buf = rbuf();
        INSIST( rbuf_strcpy( &buf, "hello" ) );
        INSIST( rbuf_strcat( &buf, " " ) );
        INSIST( rbuf_strcat( &buf, "world" ) );
        INSIST( rbuf_strcat( &buf, "!" ) );
        INSIST( rbuf_strcmp( &buf, "hello world!" ) == 0 );

        INSIST( rbuf_strcpy( &buf, "..." ) );
        INSIST( rbuf_strcmp( &buf, "..." ) == 0 );
        rval_release( &buf );
    } RTEST_END;

    RTEST_BEGIN( "rval / buf / strcpy, strcat, strcmp (zero-length cstr)" )  {
        RVal buf = rbuf();
        INSIST( rbuf_strcpy( &buf, "hello" ) );
        INSIST( rbuf_strcat( &buf, "" ) );
        INSIST( rbuf_strcmp( &buf, "hello" ) == 0 );
        INSIST( rbuf_strcmp( &buf, "" ) != 0 );
        INSIST( strlen( rbuf_strget( &buf ) ) == 5 );

        INSIST( rbuf_strcpy( &buf, "" ) );
        INSIST( rbuf_len( &buf ) == 0 );

        rval_release( &buf );
    } RTEST_END;

    RTEST_BEGIN( "rval / buf / strcpy, strcat, strcmp (null cstr)" )  {
        RVal buf = rbuf();
        INSIST( rbuf_strcpy( &buf, "hello" ) );

        INSIST( !rbuf_strcat( &buf, 0 ) );
        INSIST( !rbuf_strcat( &buf, 0 ) );
        INSIST( !rbuf_strcpy( &buf, 0 ) );

        INSIST( rbuf_strcmp( &buf, "hello" ) == 0 );

        rval_release( &buf );
    } RTEST_END;

    RTEST_BEGIN( "rval / buf / cpy, cat, cmp" )  {
        RVal a = rbuf();
        RVal b = rbuf();
        INSIST( rbuf_strcat( &a, "hello" ) );
        INSIST( rbuf_strcpy( &b, " world!" ) );

        INSIST( rbuf_cat( &a, &b ) );
        INSIST( rbuf_strcmp( &a, "hello world!" ) == 0 );
        INSIST( rbuf_cmp( &a, &b ) != 0 );

        INSIST( rbuf_strcpy( &b, "..." ) );
        INSIST( rbuf_cpy( &a, &b ) );
        INSIST( rval_eq( &a, &b ) );

        rval_release( &a );
        rval_release( &b );
    } RTEST_END;

    RTEST_BEGIN( "rval / buf / clear" )  {
        RVal buf = rbuf();
        INSIST( rbuf_strcpy( &buf, "hello" ) );
        INSIST( rbuf_clear( &buf ) );
        INSIST( rbuf_clear( &buf ) );
        INSIST( rbuf_len( &buf ) == 0 );
        rval_release( &buf );
    } RTEST_END;

    RTEST_BEGIN( "rval / buf / survives resizing" )  {
        RVal buf = rbuf();
        INSIST( rbuf_strcpy( &buf, "hello" ) );
        INSIST( rbuf_reserve( &buf, 100 ) );
        INSIST( rbuf_compact( &buf ) );
        INSIST( rbuf_strcmp( &buf, "hello" ) == 0 );
        rval_release( &buf );
    } RTEST_END;


}

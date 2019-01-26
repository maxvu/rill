#include "test.h"

#include <stdio.h>

void rtest_init () {
    __rts.tot.n = 0;
    __rts.tot.n_pass = 0;
    __rts.cur.n = 0;
    __rts.cur.n_pass = 0;
    __rts.cur.name = rnil();
    rbuf_init( &__rts.cur.name, 128 );
    __rts.cur.msg = rnil();
    rbuf_init( &__rts.cur.msg, 128 );
}

void rtest_test_begin ( const char * test_name ) {
    __rts.cur.n = 0;
    __rts.cur.n_pass = 0;
    rbuf_strcpy( &__rts.cur.name, test_name );
    rbuf_clear( &__rts.cur.msg );
}

void rtest_test_end () {
    if ( __rts.cur.n == __rts.cur.n_pass ) {
        printf( RILL_CONSOLE_GREEN "[ ok ] %s\n" RILL_CONSOLE_CLEAR, rbuf_strget( &__rts.cur.name ) );
    } else {
        printf( RILL_CONSOLE_RED "[ xx ] %s\n" RILL_CONSOLE_CLEAR, rbuf_strget( &__rts.cur.name ) );
        printf( "    %s\n", rbuf_strget( &__rts.cur.msg ) );
    }
    __rts.tot.n += __rts.cur.n;
    __rts.tot.n_pass += __rts.cur.n_pass;
}

void rill_test_all () {
    rill_test_rval();
    rill_test_utf8();
}

void rtest_test_cleanup () {
    rval_release( &__rts.cur.name );
    rval_release( &__rts.cur.msg );
}

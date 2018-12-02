#include <string.h>

#include "rill_test.h"

RTestState ___rtest;

void ___rtest_msgbuf_reset () {
    memset( ___rtest.msgbuf, 0, RILL_TEST_MSG_BUFFER_LENGTH );
    ___rtest.msgbuf_len = 0;
}

void ___rtest_msgbuf_append ( const char * msg ) {
    size_t msg_len = strlen( msg );
    if ( msg_len ) {
        snprintf(
            ___rtest.msgbuf + ___rtest.msgbuf_len,
            RILL_TEST_MSG_BUFFER_LENGTH - ___rtest.msgbuf_len,
            "%s",
            msg
        );
        ___rtest.msgbuf_len += msg_len;
    }
}

void ___rtest_init () {
    ___rtest.n_conds = 0;
    ___rtest.n_conds_passed = 0;
    ___rtest.n_tests = 0;
    ___rtest.n_tests_passed = 0;
    ___rtest_msgbuf_reset();
}

void ___rtest_begin ( char * name ) {
    ___rtest_msgbuf_reset();
    strncpy( ___rtest.current_test_name, name, RILL_TEST_NAME_BUFFER_LENGTH );
    ___rtest.current_test_passing = 1;
}

void ___rtest_insist ( const char * cond_text, int cond, const char * file, size_t line ) {
    ___rtest.n_conds++;
    if ( cond ) {
        ___rtest.n_conds_passed++;
    } else {
        ___rtest.current_test_passing = 0;

        ___rtest.msgbuf_len -= snprintf(
            ___rtest.msgbuf,
            RILL_TEST_NAME_BUFFER_LENGTH - ___rtest.msgbuf_len,
            "    " RILL_CONSOLE_FAILURE( %s ) " @ %s:%lu" "\n",
            cond_text, file, line
        );
    }
}

void ___rtest_end () {
    if ( ___rtest.current_test_passing ) {
        printf( RILL_CONSOLE_SUCCESS( [ OK ] %s ) "\n", ___rtest.current_test_name );
    } else {
        printf( RILL_CONSOLE_FAILURE( [ !! ] %s ) "\n", ___rtest.current_test_name );
        printf( "%s\n", ___rtest.msgbuf );
    }
}

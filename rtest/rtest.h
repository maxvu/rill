#ifndef __RTEST
#define __RTEST

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RILL_TEST_TESTNAME_LIMIT    64
#define RILL_TEST_FILENAME_LIMIT    64
#define RILL_TEST_ASSERT_LIMIT      64
#define RILL_TEST_ASSERT_TEXT_LIMIT 128

static size_t n_tests_run;
static size_t n_tests_passed;

typedef struct rassert {
    char text[ RILL_TEST_ASSERT_TEXT_LIMIT ];
    size_t line;
    char pass;
} rassert;

typedef struct rtest {
    char name[ RILL_TEST_TESTNAME_LIMIT ];
    char filename[ RILL_TEST_FILENAME_LIMIT ];
    char pass;
    char n_asserts;
    rassert asserts[ RILL_TEST_ASSERT_LIMIT ];
} rtest;

static rtest ___test;

void rtest_init ( rtest * test ) {
    n_tests_run = 0;
    n_tests_passed = 0;
}

void rtest_set (
    rtest * test,
    const char * name,
    const char * filename
) {
    strncpy( test->name, name, RILL_TEST_TESTNAME_LIMIT );
    strncpy( test->filename, filename, RILL_TEST_FILENAME_LIMIT );
    test->n_asserts = 0;
    test->pass = 1;
    memset( test->asserts, 0, sizeof( rassert ) * RILL_TEST_ASSERT_LIMIT );
}

int rtest_assert (
    rtest * test,
    const char * text,
    size_t line,
    char pass
) {
    if ( test->n_asserts == RILL_TEST_ASSERT_LIMIT - 1 ) {
        printf( "max assert limit reached -- exiting" );
        exit( 127 );
    }
    rassert * assert = test->asserts + test->n_asserts++;
    strncpy( assert->text, text, RILL_TEST_ASSERT_TEXT_LIMIT );
    assert->line = line;
    assert->pass = pass;
    if ( !assert->pass )
        test->pass = 0;
    else
        ++n_tests_passed;
    ++n_tests_run;
    return 1;
}

void rtest_end ( rtest * test ) {

}

void rtest_print ( rtest * test ) {
    const char * green = "\033[1;32m";
    const char * red   = "\033[1;31m";
    const char * clear = "\033[0m";
    if ( test->pass ) {
        printf(
            "%s[ OK ] %s%s\n",
            green, test->name,
            clear
        );
    } else {
        printf( "[ !! ] %s%s\n", test->name, clear );
        rassert * assert;
        for ( size_t i = 0; i < test->n_asserts; i++ ) {
            assert = &test->asserts[ i ];
            if ( assert->pass ) {
                printf(
                    "    [ OK ] %s | %s:%lu\n",
                    assert->text,
                    test->filename,
                    assert->line
                );
            } else {
                printf(
                    "    %s[ !! ] %s | %s:%lu%s\n",
                    red,
                    assert->text,
                    test->filename,
                    assert->line,
                    clear
                );
            }
        }
    }
}

#define RTEST_INIT do { n_tests_run = 0; n_tests_passed = 0; rtest_init( &___test ); } while ( 0 )
#define RTEST( name ) rtest_set( &___test, name, __FILE__ );
#define ASSERT( cond ) rtest_assert( &___test, #cond, __LINE__, cond )
#define RTEST_END do { rtest_end( &___test ); rtest_print( &___test ); } while ( 0 )
#define RTEST_OK ( n_tests_run == n_tests_passed )
#define RTEST_NUM_TESTS ( n_tests_run )
#define RTEST_NUM_PASSED ( n_tests_passed )
#define DEBUGGER raise( SIGINT );

#endif

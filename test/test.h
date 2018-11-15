#include <string.h>
#include <stdio.h>

#ifndef RILL_TEST_H
#define RILL_TEST_H

#define CONSOLE_GREEN "\033[1;32m"
#define CONSOLE_RED "\033[1;31m"
#define CONSOLE_RESET "\033[0m"
#define MSG_BUF_CAP 700

extern unsigned int ___test_options;
extern unsigned int ___assertions_count;
extern unsigned int ___assertions_passed;
extern unsigned int ___tests_count;
extern unsigned int ___tests_passed;

#define MAKE_RED( MSG ) CONSOLE_RED MSG CONSOLE_RESET
#define MAKE_GREEN( MSG ) CONSOLE_GREEN MSG CONSOLE_RESET

#define INSIST( CONDITION ) do { \
    ___assertions_count++; \
    if ( CONDITION ) { \
        ___assertions_passed++; \
    } else { \
        ___msg_buf_len += snprintf( \
            ___msg_buf + ___msg_buf_len, \
            MSG_BUF_CAP - ___msg_buf_len, \
            "  " MAKE_RED( "%s" ) " %s:%d\n", \
            #CONDITION, \
            __FILE__, \
            __LINE__ \
        ); \
        ___passed = 0; \
    } \
} while ( 0 );

#define RILL_TEST( NAME, BODY ) do { \
    int ___passed = 1; \
    char ___msg_buf[MSG_BUF_CAP]; \
    unsigned long ___msg_buf_len = 0; \
    { BODY; } \
    ___tests_count++; \
    if ( ___passed ) { \
        ___tests_passed++; \
        printf( MAKE_GREEN( "%s" ) "\n", NAME ); \
    } else { \
        printf( MAKE_RED( "%s" ) "\n", NAME ); \
        printf( MAKE_RED( "%s" ) "\n", ___msg_buf ); \
    } \
} while ( 0 );

#endif

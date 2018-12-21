#include "rill_test.h"

#include <string.h>

char __rill_current_test_name[ RILL_TEST_NAME_BUFFER_SIZE ];
size_t __rill_current_test_n_assertions;
size_t __rill_current_test_n_passing;
size_t __rill_all_tests_passing = 1;

void rtest_begin ( const char * name ) {
    memset( &__rill_current_test_name, 0, RILL_TEST_NAME_BUFFER_SIZE );
    strncpy( __rill_current_test_name, name, RILL_TEST_NAME_BUFFER_SIZE );
    __rill_current_test_n_assertions = 0;
    __rill_current_test_n_passing = 0;
}

void rtest_end () {
    if ( __rill_current_test_n_assertions == __rill_current_test_n_passing ) {
        printf(
            CONSOLE_GREEN CONSOLE_CHAR_MARKYES " %s" CONSOLE_RESET "\n",
            __rill_current_test_name
        );
    } else {
        __rill_all_tests_passing = 0;
        printf(
            CONSOLE_RED CONSOLE_CHAR_MARKNO " %s" CONSOLE_RESET "\n",
            __rill_current_test_name
        );
    }
}

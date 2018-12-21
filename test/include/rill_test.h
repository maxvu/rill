#include <stdio.h>

#define CONSOLE_GREEN "\033[1;32m"
#define CONSOLE_RED "\033[1;31m"
#define CONSOLE_RESET "\033[0m"

#define CONSOLE_CHAR_MARKYES "[ ok ]"
#define CONSOLE_CHAR_MARKNO  "[ !! ]"

#define RILL_TEST_NAME_BUFFER_SIZE 256

char __rill_current_test_name[ RILL_TEST_NAME_BUFFER_SIZE ];
size_t __rill_current_test_n_assertions;
size_t __rill_current_test_n_passing;
size_t __rill_all_tests_passing;

#define insist( COND ) do { ++__rill_current_test_n_assertions; if ( !(COND) ) { printf( "%s, %s:%d\n", #COND, __FILE__, __LINE__ ); } else { ++__rill_current_test_n_passing; } } while ( 0 );

void rtest_begin ( const char * name );
void rtest_end ();

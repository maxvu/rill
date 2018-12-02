#include <stdio.h>

#include "environment.h"

#define RILL_TEST_NAME_BUFFER_LENGTH 128
#define RILL_TEST_MSG_BUFFER_LENGTH 512

typedef struct RTestState {
    size_t n_conds;
    size_t n_conds_passed;
    size_t n_tests;
    size_t n_tests_passed;

    int current_test_passing;
    char current_test_name[ RILL_TEST_NAME_BUFFER_LENGTH ];

    char msgbuf[ RILL_TEST_MSG_BUFFER_LENGTH ];
    size_t msgbuf_len;
} RTestState;

void ___rtest_msgbuf_reset ();
void ___rtest_msgbuf_append ( const char * msg );

void ___rtest_init ();
void ___rtest_begin ( char * name );
void ___rtest_insist ( const char * cond_text, int cond, const char * file, size_t line );
void ___rtest_end ();

#define TEST_BEGIN( NAME ) ___rtest_begin( NAME ) ;
#define INSIST( CONDITION ) ___rtest_insist( #CONDITION, CONDITION, __FILE__, __LINE__ ) ;
#define TEST_END ___rtest_end() ;

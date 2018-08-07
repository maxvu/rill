#include <stdio.h>

#include "val/rval.h"
#include "val/rmap.h"
#include "val/rvec.h"
#include "val/rstr.h"

/* file: minunit.h */
#define insist(test, msg) do { \
    if (test) { printf("OK  %s\n", msg); n_passed++; } \
    else printf("!! %s\n", msg); \
    n_run++; } while ( 0 )

int n_run = 0;
int n_passed = 0;

void test_val () {

    {
        RStr some_message;
        rstr_init( &some_message, 64 );
        insist( rstr_len( &some_message ) == 0, "new string's len is 0" );
        rstr_release( &some_message );
    }

}

int main ( int argc, char ** argv ) {

    test_val();

    printf( "%d tests run\n", n_run );
    printf( "%d tests passed\n", n_passed );

    return n_run == n_passed;
}

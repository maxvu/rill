#include "minunit.h"

#include <stdio.h>

int tests_run = 0;
int num_asserts = 0;

char * test_rvec ();

int main ( int argc, char ** argv ) {

    char * message;
    if ( ( message = test_rvec() ) ) {
        printf( "FAILED: %s\n", message );
    } else {
        printf( "OK\n" );
    }

    printf( "%d tests run\n", tests_run );
    printf( "%d assertions run\n", num_asserts );

    return message == NULL;

}

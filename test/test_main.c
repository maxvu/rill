#include "test.h"

#include <stdio.h>

int num_asserts = 0;
int num_success = 0;

char * test_rval ();

void insist ( char cond, const char * label ) {
    num_asserts++;
    if ( cond ) {
        printf( "OK   %s\n", label );
        num_success++;
    } else {
        printf( "FAIL %s\n", label );
    }
}

int main ( int argc, char ** argv ) {

    insist( 1 + 1 == 2, "1 + 1 == 2" );

    test_rval();

    return 0;

}

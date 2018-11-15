#include <stdio.h>

#include "test.h"

unsigned int ___test_options = 0;
unsigned int ___assertions_count = 0;
unsigned int ___assertions_passed = 0;
unsigned int ___tests_count = 0;
unsigned int ___tests_passed = 0;

void ___debug () {}
void test_rval ();

int main ( int argc, char ** argv ) {

    RILL_TEST( "sanity", ({
        INSIST( 1 + 1 == 2 );
    }) );

    test_rval();

    if ( ___assertions_count == ___assertions_passed ) {
        printf( CONSOLE_GREEN "\n" );
    } else {
        printf( CONSOLE_RED "\n" );
    }

    printf(
        "%u / %u tests passed\n",
        ___tests_passed,
        ___tests_count
    );
    printf(
        "%u / %u assertions passed\n",
        ___assertions_passed,
        ___assertions_count
    );

    printf( CONSOLE_RESET "\n" );
    if ( ___assertions_count == ___assertions_passed ) {
        return 0;
    } else {
        return 1;
    }

}

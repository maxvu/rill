#include "test/test.h"
#include "test/manifest.h"

unsigned int ___test_options = 0;
unsigned int ___test_count = 0;
unsigned int ___tests_passed = 0;
unsigned int ___assertions_count = 0;
unsigned int ___assertions_passed = 0;

void ___debug () { /* ... */ }

int main ( int argc, char ** argv ) {
    test( "sanity check", {
        insist( 1 + 1 == 2 );
    } );

    __run_all_tests();

    printf( "\n" );
    if ( ___tests_count == ___tests_passed ) {
        printf(
            CONSOLE_GREEN "%d assertions passed\n" CONSOLE_RESET,
            ___tests_count
        );
        return 0;
    } else {
        printf(
            CONSOLE_RED "%d / %d assertions passed\n" CONSOLE_RESET,
            ___tests_passed,
            ___tests_count
        );
        return 0;
    }
}

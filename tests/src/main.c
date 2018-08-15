#include "test.h"

int main ( int argc, char ** argv ) {
    test( "sanity check, fail", {
        insist( strcmp( "OK", "OK" ) == 0 );
        insist( 1 + 1 == 3 );
    } );

    test( "sanity check, pass", {
        insist( strcmp( "OK", "OK" ) == 0 );
        insist( 1 + 1 == 2 );
        insist( 2 + 2 == 4 );
    } );

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

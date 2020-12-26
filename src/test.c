#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test.h"

int  rill_test_ok;
char rill_test_name[ 512 ];

void rill_test_begin ( const char * name ) {
    if ( !name ) {
        printf( "** no test name given **" );
        exit( 325 );
    }
    strncpy( rill_test_name, name, 511 );
    rill_test_ok = 1;
}

void rill_test_end () {
    if ( rill_test_ok ) {
        printf( "%s[ OK ] %s%s\n", "\x1b[32m", rill_test_name, "\x1b[0m" );
        strcat( rill_test_name, "" );
    } else {

    }
}

int rill_run_tests () {
    #include "../test/manifest.c"
    return rill_test_ok;
}

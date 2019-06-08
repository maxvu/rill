#include "../../test/test.h"

#include <stdio.h>
#include <string.h>

#define RILL_BUFFER_LENGTH 1024
char ___RILL_TEST_NAME[ RILL_BUFFER_LENGTH ];
char ___RILL_ASSERT_TEXT[ RILL_BUFFER_LENGTH ];
#define __TO_STRING(i) #i
#define TO_STRING(i) __TO_STRING(i)

#define RTEST( name ) strncpy( ___RILL_TEST_NAME, name, RILL_BUFFER_LENGTH );
#define RMUST( cond ) if ( cond ) { printf( "[ OK ] "); } else { printf( "[ !! ]"); } printf( "%s / %s @ %s:%d", ___RILL_TEST_NAME, #cond, __FILE__, __LINE__ )
#define RTEST_END ___RILL_TEST_NAME[ 0 ] = 0;

int main ( int argc, char ** argv ) {

    #include "sanity.inc"
    
    printf( "\n" );
    
    return 0;

}
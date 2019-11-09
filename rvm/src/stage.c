#include <stdio.h>
#include <stdint.h>

#include "rval.h"

int main ( int argc, char ** argv ) {
    printf( "rval: %lu\n", sizeof( rval ) );
    printf( "rstr: %lu\n", sizeof( rstr ) );
    printf( "rvec: %lu\n", sizeof( rvec ) );
    printf( "rmap: %lu\n", sizeof( rmap ) );
    printf( "size_t: %lu\n", sizeof( size_t ) );
    printf( "unsigned int: %lu\n", sizeof( unsigned int ) );
    printf( "int_fast32_t: %lu\n", sizeof( int_fast32_t ) );
    printf( "ok\n" );
    return 0;
}

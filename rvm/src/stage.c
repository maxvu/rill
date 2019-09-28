#include <stdio.h>
#include <stdint.h>

#include "rerr.h"
#include "rval.h"
#include "rvec.h"
#include "rmap.h"

int main ( int argc, char ** argv ) {
    printf( "rval: %lu\n", sizeof( rval ) );
    printf( "size_t: %lu\n", sizeof( size_t ) );
    printf( "unsigned int: %lu\n", sizeof( unsigned int ) );
    printf( "int_fast32_t: %lu\n", sizeof( int_fast32_t ) );
    printf( "ok\n" );
    return 0;
}

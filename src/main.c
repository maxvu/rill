#include <stdio.h>

#include "rval.h"
#include "rnum.h"

int main ( int argc, char ** argv ) {
    printf( "size of int:  %lu\n", sizeof( int ) );
    printf( "size of rnum: %lu\n", sizeof( rnum ) );
    printf( "ok\n" );

    return 0;
}

#include <stdio.h>

#include "rval.h"
#include "rval_impl.h"

int main ( int argc, char ** argv ) {
    printf( "sizeof( rval ) = %lu\n", sizeof( rval ) );
    printf( "OK\n" );
    return 0;
}

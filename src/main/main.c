#include <stdio.h>

#include "rval.h"
#include "rval_impl.h"

int main ( int argc, char ** argv ) {
    printf( "rnum: %lu\n", sizeof ( rnum ) );
    printf( "rstr: %lu\n", sizeof ( rstr ) );
    printf( "rvec: %lu\n", sizeof ( rvec ) );
    printf( "rmap: %lu\n", sizeof ( rmap ) );
    return 0;
}

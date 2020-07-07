#include <stdio.h>

#include "array.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "string.hpp"

using rill::array;

int main ( int argc, char ** argv ) {
    printf( "ok\n" );
    array<int> nums( 5 );
    nums[ 3 ] = 0;
    return 0;
}

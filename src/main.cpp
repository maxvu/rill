#include <stdio.h>

#include "array.hpp"
#include "vector.hpp"
// #include "map.hpp"
// #include "string.hpp"

using rill::array;
using rill::vector;

int main ( int argc, char ** argv ) {
    printf( "ok\n" );
    vector<int> nums( 5 );
    for ( auto i = 0; i < 10; i++ )
        nums.push( i );

    printf( "length: %lu", nums.length() );
    printf( "capacity: %lu", nums.capacity() );

    return 0;
}

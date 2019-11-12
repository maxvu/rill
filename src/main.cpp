#include "map.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "rval.hpp"

#include <cstdio>

using rill::rval;

int main ( int argc, char ** argv ) {
    printf( "rval: %ld\n", sizeof( rval ) / sizeof( int ) );
    printf( "ok\n" );
    return 0;
}

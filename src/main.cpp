#include <cstdio>
#include "buffer.hpp"
#include "array.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "val.hpp"

using rill::vector;
using rill::numval;
using rill::vecval;
using rill::mapval;

int main ( int argc, char ** argv ) {
    printf( "sizeof %s: %lu\n", "numval", sizeof( numval ) );
    printf( "OK\n" );
    return 0;
}

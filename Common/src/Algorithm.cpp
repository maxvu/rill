#include <cstdint>
#include <cstddef>
#include <cstring>

#include "Algorithm.hpp"
#include "Error.hpp"

namespace Rill {

template <typename T> const T & min ( const T & a, const T & b ) {
    if ( a < b )
        return a;
    return b;
}

};

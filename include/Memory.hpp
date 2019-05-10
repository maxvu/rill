#ifndef RILL_MEMORY
#define RILL_MEMORY

#include <cstddef>
#include <new>

#include "Error.hpp"

namespace Rill {

    template <typename T> T * allocate () {
        T * mem = new ( std::nothrow ) T;
        if ( !mem )
            throw OOMError();
        return mem;
    }

    template <typename T> T * allocate ( size_t n ) {
        T * mem = new ( std::nothrow ) T[ n ];
        if ( !mem )
            throw OOMError();
        return mem;
    }

}

#endif

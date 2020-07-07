#ifndef RILL_ALLOC
#define RILL_ALLOC

#include <new>

#include "error.hpp"

namespace rill {

    template <typename T> T * alloc () {
        T * mem = new ( std::nothrow ) T;
        if ( !mem )
            throw oom_error();
        return mem;
    }

    template <typename T> void dealloc ( T * mem ) {
        delete mem;
    }

    template <typename T> T * alloc_n ( size_t n ) {
        T * mem = new ( std::nothrow ) T[ n ];
        if ( !mem )
            throw oom_error();
        return mem;
    }

    template <typename T> void dealloc_n ( T * mem ) {
        delete[] mem;
    }

}

#endif

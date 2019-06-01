#ifndef RILL_MEMORY
#define RILL_MEMORY

#include <cstddef>
#include <new>

#include "Error.hpp"

namespace Rill {

    template <typename T> T * createOne ();
    template <typename T> T * createArray ( size_t n );

    template <typename T> void destroyOne ( T * item );
    template <typename T> void destroyArray ( T * items );

}

#endif

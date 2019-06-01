#include "Memory.hpp"

namespace Rill {

template <typename T> T * createOne () {
    T * mem = new ( std::nothrow ) T;
    if ( !mem )
        throw OOMError();
    return mem;
}

template <typename T> T * createArray ( size_t n ) {
    T * mem = new ( std::nothrow ) T[ n ];
    if ( !mem )
        throw OOMError();
    return mem;
}

template <typename T> void destroyOne ( T * item ) {
    delete item;
}

template <typename T> void destroy ( T * items ) {
    delete[] items;
}

}

// #include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
// #include <utility>

#include "BufferBytesView.hpp"
#include "Error.hpp"

namespace Rill {

BufferBytesView & BufferBytesView::set ( uint8_t * mem, size_t mem_length ) {
    if ( !mem_length )
        return this->clear().asBytes();
    this->reserve( mem_length );
    memcpy( this->bytes, mem, mem_length );
    this->bytes[ this->len ] = 0;
    return *this;
}

BufferBytesView & BufferBytesView::cat ( uint8_t * mem, size_t mem_length ) {
    if ( !mem_length )
        return *this;
    this->reserve( this->len + mem_length );
    memcpy( this->bytes + this->len, mem, mem_length );
    this->bytes[ this->len ] = 0;
    return *this;
}

bool BufferBytesView::eq ( uint8_t * mem, size_t mem_length ) const {
    if ( this->len != mem_length )
        return 0;
    return memcmp( this->bytes, mem, mem_length ) == 0;
}

uint8_t & BufferBytesView::operator[] ( size_t index ) {
    if ( index >= this->len )
        throw OOBError();
    return this->bytes[ index ];
}

uint8_t BufferBytesView::operator[] ( size_t index ) const {
    if ( index >= this->len )
        throw OOBError();
    return this->bytes[ index ];
}

BufferBytesView::operator uint8_t * () {
    return this->bytes;
}

BufferBytesView::operator const uint8_t * () const {
    return this->bytes;
}

BufferBytesView & BufferBytesView::fill ( uint8_t byte ) {
    memset( this->bytes, byte, this->len );
    return *this;
}

}

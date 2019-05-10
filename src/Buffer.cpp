#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <utility>

#include "Buffer.hpp"
#include "Error.hpp"
#include "Memory.hpp"

namespace Rill {

Buffer & Buffer::resize ( size_t new_capacity ) {
    assert( new_capacity >= this->len + 1 );
    uint8_t * new_bytes = allocate<uint8_t>( new_capacity );
    memcpy( new_bytes, this->bytes, this->len + 1 );
    delete[] this->bytes;
    this->bytes = new_bytes;
    this->cap = new_capacity;
    return *this;
}

Buffer::Buffer () : Buffer( RILL_BUFFER_DEFAULT_SIZE ) {

}

Buffer::Buffer ( size_t initial_capacity ) {
    if ( initial_capacity < RILL_BUFFER_MINIMUM_SIZE )
        initial_capacity = RILL_BUFFER_MINIMUM_SIZE;
    this->bytes = allocate<uint8_t>( initial_capacity + 1 );
    this->bytes[ 0 ] = 0;
    this->len = 0;
    this->cap = initial_capacity;
}

Buffer::Buffer ( uint8_t * mem, size_t mem_length ) : Buffer( mem_length ) {
    this->set( mem, mem_length );
}

Buffer::Buffer ( const Buffer & that ) : Buffer( that.length() + 1 ) {
    *this = that;
}

Buffer::Buffer ( const Buffer && that ) {
    this->bytes = that.bytes;
    this->len = that.len;
    this->cap = that.cap;
}

Buffer::~Buffer () {
    delete[] this->bytes;
}

size_t Buffer::length () const {
    return this->len;
}

Buffer & Buffer::reserve ( size_t new_capacity ) {
    if ( this->cap < new_capacity + 1 )
        return this->resize( new_capacity );
    return *this;
}

Buffer & Buffer::compact () {
    if ( this->cap != this->len + 1 )
        return this->resize( this->cap );
    return *this;
}

Buffer Buffer::operator+ ( const Buffer & that ) const {
    return Buffer( *this ) += that;
}

Buffer & Buffer::operator+= ( const Buffer & that ) {
    return this->cat( that.bytes, that.len );
}

bool Buffer::operator== ( const Buffer & that ) const {
    if ( this->len != that.len )
        return false;
    return memcmp( this->bytes, that.bytes, this->len );
}

bool Buffer::operator!= ( const Buffer & that ) const {
    return !( *this == that );
}

Buffer & Buffer::operator= ( const Buffer & that ) {
    return this->set( that.bytes, that.len );
}

Buffer & Buffer::set ( uint8_t * mem, size_t mem_length ) {
    if ( !mem_length )
        return this->clear();
    this->reserve( mem_length );
    memcpy( this->bytes, mem, mem_length );
    this->bytes[ this->len ] = 0;
    return *this;
}

Buffer & Buffer::cat ( uint8_t * mem, size_t mem_length ) {
    if ( !mem_length )
        return *this;
    this->reserve( this->len + mem_length );
    memcpy( this->bytes + this->len, mem, mem_length );
    this->bytes[ this->len ] = 0;
    return *this;
}

bool Buffer::eq ( uint8_t * mem, size_t mem_length ) const {
    if ( this->len != mem_length )
        return 0;
    return memcmp( this->bytes, mem, mem_length ) == 0;
}

uint8_t & Buffer::operator[] ( size_t index ) {
    if ( index >= this->len )
        throw OOBError();
    return this->bytes[ index ];
}

uint8_t Buffer::operator[] ( size_t index ) const {
    if ( index >= this->len )
        throw OOBError();
    return this->bytes[ index ];
}

Buffer::operator uint8_t * () {
    return this->bytes;
}

Buffer::operator const uint8_t * () const {
    return this->bytes;
}

Buffer & Buffer::fill ( uint8_t byte ) {
    memset( this->bytes, byte, this->len );
    return *this;
}

Buffer & Buffer::clear () {
    this->bytes[ 0 ] = 0;
    this->len = 0;
    return *this;
}

}

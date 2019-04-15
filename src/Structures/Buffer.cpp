#include "Structures/Buffer.hpp"

#include <string>
#include <cstring>

namespace Rill {

Buffer::Buffer () {

}

Buffer::Buffer ( size_t init_size ) : bytes( init_size ) {

}

Buffer::Buffer ( const char * cstr ) {
    std::string asString( cstr );
    this->bytes = std::vector<uint8_t>( asString.begin(), asString.end() );
}

Buffer::Buffer ( const Buffer & that ) : bytes( that.bytes ) {

}

Buffer::Buffer ( const Buffer && that ) {
    this->bytes = std::move( that.bytes );
}

Buffer::~Buffer () {

}

size_t Buffer::length () const {
    return this->bytes.size();
}

size_t Buffer::capacity () const {
    return this->bytes.capacity();
}

Buffer & Buffer::reserve ( size_t new_capacity ) {
    this->bytes.reserve( new_capacity );
    return *this;
}

Buffer & Buffer::compact () {
    this->bytes.shrink_to_fit();
    return *this;
}

Buffer & Buffer::operator+= ( const Buffer & that ) {
    this->bytes.insert(
        this->bytes.end(),
        that.bytes.begin(),
        that.bytes.end()
    );
    return *this;
}

Buffer & Buffer::operator= ( const Buffer & that ) {
    this->bytes = that.bytes;
    return *this;
}

bool Buffer::operator== ( const Buffer & that ) const {
    return this->bytes == that.bytes;
}

Buffer::operator bool () const {
    return this->length() > 0;
}

ByteBuffer & Buffer::asBytes () {
    return *( static_cast<ByteBuffer*>( this ) );
}

CharBuffer & Buffer::asChars () {
    return *static_cast<CharBuffer*>( this );
}

UTF8Buffer & Buffer::asUTF8 () {
    return *static_cast<UTF8Buffer*>( this );
}

const ByteBuffer & Buffer::asBytes () const {
    return this->asBytes();
}

const CharBuffer & Buffer::asChars () const {
    return this->asChars();
}

const UTF8Buffer & Buffer::asUTF8  () const {
    return this->asUTF8();
}

ByteBuffer & ByteBuffer::set ( uint8_t * mem, size_t mem_len ) {
    this->reserve( mem_len );
    memcpy( this->bytes.data(), mem, mem_len );
    return *this;
}

ByteBuffer & ByteBuffer::cat ( uint8_t * mem, size_t mem_len ) {
    this->reserve( this->length() + mem_len );
    memcpy( this->bytes.data() + this->length(), mem, mem_len );
    return *this;
}

char ByteBuffer::cmp ( uint8_t * mem, size_t mem_len ) const {
    mem_len = std::min( mem_len, this->length() );
    return memcmp( this->bytes.data(), mem, mem_len );
}

uint8_t ByteBuffer::operator[] ( size_t index ) {
    return this->bytes[ index ];
}

ByteBuffer::operator const uint8_t * () const {
    return this->bytes.data();
}

CharBuffer & CharBuffer::operator= ( const char * cstr ) {
    Buffer fromChar( cstr );
    *static_cast<Buffer*>( this ) = fromChar;
    return *this;
}

CharBuffer & CharBuffer::operator+= ( const char * cstr ) {
    Buffer fromCString( cstr );
    *static_cast<Buffer*>( this ) += cstr;
    return *this;
}

char CharBuffer::operator[] ( size_t index ) {
    return this->bytes[ index ];
}

CharBuffer::operator const char * () const {
    return ( const char * ) this->bytes.data();
}

UTF8Buffer::Iter::Iter ( const UTF8Buffer & buffer )
    : it( buffer.bytes.begin() ),
      end( buffer.bytes.end() )
{

}

UTF8Buffer::Iter & UTF8Buffer::Iter::operator++ (int) const {
    if ( *this )
        this->it++;
    return *this;
}

UTF8Buffer::Iter::operator bool () const {
    return this->it != this->end;
}

int UTF8Buffer::Iter::codepoint () const {
    // ???
}

UTF8Buffer::Iter UTF8Buffer::begin () const {
    return Iter( *this );
}

size_t UTF8Buffer::length () const {

}

}

#include <cstring>

#include "Algorithm.hpp"
#include "Buffer.hpp"
#include "Error.hpp"
#include "Memory.hpp"

namespace Rill {

Buffer::Buffer ( size_t init_size ) : siz( init_size ) {
    if ( !init_size )
        throw ArgError( "Buffer::Buffer", "init_size" );
    this->byt = createArray<uint8_t>( init_size );
}

Buffer::Buffer ( uint8_t * bytes, size_t bytes_len ) : Buffer( bytes_len ) {
    std::memcpy( this->byt, bytes, bytes_len );
}

Buffer::Buffer ( const Buffer & that ) : Buffer( that.siz ) {
    std::memcpy( *this, that, that.siz );
}

Buffer::~Buffer () {
    destroyArray( this->byt );
}

size_t Buffer::size () const {
    return this->siz;
}

Buffer & Buffer::resize ( size_t new_size ) {
    Buffer tmp( new_size );
    std::memcpy( tmp, *this, min( this->size(), new_size ) );
    *this = tmp;
    return *this;
}

Buffer::operator uint8_t * () {
    return this->byt;
}

Buffer::operator const uint8_t * () const {
    return this->byt;
}

char * Buffer::asChar () {
    return ( char * ) this->byt;
}

const char * Buffer::asChar () const {
    return ( const char * ) this->byt;
}

Buffer & Buffer::zero () {
    std::memset( this->byt, 0, this->siz );
    return *this;
}

}

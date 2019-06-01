#include "Buffer.hpp"
#include "Error.hpp"
#include "Memory.hpp"
#include "String.hpp"

namespace Rill {

String & String::resize ( size_t new_length ) {
    if ( new_length < this->len + 1 )
        throw OOBError();
    this->buf.resize( new_length );
    return *this;
}

String & String::terminate () {
    this->buf[ 0 ] = 0;
    return *this;
}

String::String () : String( RILL_STRING_DEFAULT_SIZE ) {
    this->terminate();
}

String::String ( size_t initial_capacity ) :
    len( 0 ),
    buf( initial_capacity + 1 )
{
    this->terminate();
}

String::String ( const char * cstr ) : String () {
    if ( !cstr )
        throw ArgError( "String::String::( const char * )", "cstr" );
    this->len = strlen( cstr );
    std::memcpy( this->buf.asChar(), ( uint8_t * ) cstr, this->len );
    this->terminate();
}

String::String ( const String & that ) : len( that.len ), buf( that.buf ) {

}

String::~String () {

}

Buffer & String::buffer () {
    return this->buf;
}

const Buffer & String::buffer () const {
    return this->buf;
}

String::operator const char * () const {
    return this->buf.asChar();
}

String & String::reserve ( size_t new_capacity ) {

}

String & String::compact () {

}


}

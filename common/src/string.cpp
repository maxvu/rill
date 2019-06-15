#include "string.hpp"

#include <cstddef>
#include <cstring>
#include <stdexcept>

namespace rill {

const size_t String::MIN_SIZE = 4;
const size_t String::DEFAULT_SIZE = 16;
const float  String::GROWTH_RATE = 2.0;

String & String::nullTerminate () {
    _buffer[ _length ] = 0;
    return *this;
}

String::String () : String( DEFAULT_SIZE ) {

}

String::String ( size_t initial_capacity )
    : _buffer( nullptr ), _length( 0 ), _capacity( 0 )
{
    if ( initial_capacity < MIN_SIZE )
        initial_capacity = MIN_SIZE;
    _buffer = new char[ initial_capacity + 1 ];
    _length = 0;
    _capacity = initial_capacity;
}

String::String ( const String & that ) : String( that._capacity ) {
    *this = that;
}

String::String ( const char * cstr ) : String() {
    if ( !cstr )
        throw std::invalid_argument( "null pointer" );
    *this = cstr;
}

String::String ( String && that ) {
    delete[] _buffer;
    _buffer = that._buffer;
    _length = that._length;
    _capacity = that._capacity;
}

String::~String () {
    delete[] _buffer;
}




}

#include "string.hpp"

#include <cstring>
#include <stdexcept>

namespace rill {

unsigned long string::MINIMUM_SIZE = 8;
unsigned long string::DEFAULT_SIZE = 16;
double        string::GROWTH_RATE  = 2.0;

string string::resize ( unsigned long new_capacity ) {
    auto _new_buffer = new char[ new_capacity ];
    memcpy( _new_buffer, _buffer, std::min( new_capacity, _capacity ) );
    delete[] _buffer;
    _buffer = _new_buffer;
    return *this;
}

string::string () : string( string::DEFAULT_SIZE ) {}

string::string ( unsigned long initial_capacity )
    : _capacity( initial_capacity )
{
    if ( _capacity < MINIMUM_SIZE )
        _capacity = MINIMUM_SIZE;
    _buffer = new char[ _capacity ];
    _length = 0;
    memset( _buffer, 0, _capacity );
}

string::string ( const string & that ) : string( that.length() ) {
    *this += that;
}

string::string ( string && that ) {
    _buffer = that._buffer;
    _length = that._length;
    _capacity = that._capacity;
}

string::string ( const char * that ) {
    if ( !that )
        throw std::invalid_argument( "null pointer" );
    unsigned long len = strlen( that );
    string tmp( len );
    if ( len )
        tmp += that;
    *this = tmp;
}

string::~string () {
    delete[] _buffer;
}

unsigned long string::length () const {
    return _length;
}

string & string::reserve ( unsigned long new_capacity ) {
    if ( new_capacity >= _capacity )
        return *this;
    resize( new_capacity );
    return *this;
}

string & string::compact () {
    resize( std::max( _length, MINIMUM_SIZE ) );
    return *this;
}

char & string::operator[] ( unsigned long index ) {
    return _buffer[ index ];
}

char string::operator[] ( unsigned long index ) const {
    return _buffer[ index ];
}

string::operator bool () const {
    return _length;
}

string::operator const char * () const {
    return _buffer;
}

string::operator unsigned char * () const {
    return ( unsigned char * ) _buffer;
}

string & string::operator+= ( const char * that ) {
    if ( !that )
        throw std::invalid_argument( "null pointer" );
    auto n = strlen( that );
    if ( n ) {
        reserve( ( _length + n ) * 2 );
        memcpy( _buffer + _length, that, n + 1 );
        _length += n;
    }
    return *this;
}

string & string::operator+= ( const string & that ) {
    reserve( ( _length + that._length ) * 2 );
    memcpy( _buffer + _length, that._buffer, that._length + 1 );
    _length += that._length;
    return *this;
}

bool string::operator== ( const string & that ) const {
    if ( _length != that._length )
        return false;
    return strncmp( _buffer, that._buffer, _length ) == 0;
}

bool string::operator!= ( const string & that ) const {
    return !( *this == that );
}

bool string::operator== ( const char * that ) const {
    if ( !that )
        throw std::invalid_argument( "null pointer" );
    return strncmp( _buffer, that, _length );
}

bool string::operator!= ( const char * that ) const {
    return !( *this == that );
}

string & string::operator= ( const string & that ) {
    reserve( that._length );
    memcpy( _buffer, that._buffer, that._length + 1 );
    _length = that._length;
    return *this;
}

string & string::operator= ( const char * that ) {
    if ( !that )
        throw std::invalid_argument( "null pointer" );
    auto n = strlen( that );
    if ( !n )
        return clear();
    reserve( n );
    memcpy( _buffer, that, n + 1 );
    _length = n;
    return *this;
}

string string::operator+ ( const string & that ) const {
    return string( *this ) += that;
}

string string::operator+ ( const char * that ) const {
    return string( *this ) += that;
}

string & string::clear () {
    _buffer[ 0 ] = 0;
    _length = 0;
    return *this;
}


}

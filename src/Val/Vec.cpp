#include "Val/Buf.hpp"
#include "Val/Vec.hpp"

#include <string>

namespace Rill {

Vec & Vec::resize ( size_t new_capacity ) {
    Val * new_vals = new Val[ new_capacity ];
    for ( size_t i = 0; i < this->len; i++ )
        new_vals[ i ] = this->vals[ i ];
    delete[] this->vals;
    this->vals = new_vals;
    this->cap = new_capacity;
    return *this;
}

Vec::Vec () : Vec( RILL_VAL_VEC_DEFAULTSIZE ) {

}

Vec::Vec ( size_t init_capacity ) {
    if ( init_capacity < RILL_VAL_VEC_MINSIZE )
        init_capacity = RILL_VAL_VEC_MINSIZE;
    this->vals = new Val[ init_capacity ];
    this->len = 0;
    this->cap = init_capacity;
}

Vec::Vec ( const Vec & other ) : Vec( other.len ) {
    *this = other;
}

Vec::~Vec () {
    delete[] this->vals;
}

Vec & Vec::operator= ( const Vec & other ) {
    this->clear();
    for ( size_t i = 0; i < other.len; i++ )
        this->push( other[ i ] );
    return *this;
}

bool Vec::operator== ( const Vec & other ) const {
    for ( size_t i = 0; i < this->len; i++ )
        if ( this->vals[ i ] != other.vals[ i ] )
            return false;
    return true;
}

bool Vec::operator!= ( const Vec & other ) const {
    return !( *this == other );
}

Vec & Vec::operator+= ( const Vec & other ) {
    for ( size_t i = 0; i < other.len; i++ )
        this->push( other[ i ] );
    return *this;
}

Val & Vec::operator[] ( size_t index ) {
    if ( index >= this->len )
        throw std::runtime_error( "OOB access on Vec" );
    return this->vals[ index ];
}

const Val & Vec::operator[] ( size_t index ) const {
    if ( index >= this->len )
        throw std::runtime_error( "OOB access on Vec" );
    return this->vals[ index ];
}

size_t Vec::length () const {
    return this->len;
}

Vec & Vec::reserve ( size_t new_capacity ) {
    if ( this->cap >= new_capacity )
        return *this;
    return this->resize( new_capacity );
}

Vec & Vec::compact () {
    size_t target = this->len;
    if ( target < RILL_VAL_VEC_MINSIZE )
        target = RILL_VAL_VEC_MINSIZE;
    if ( this->cap == target )
        return *this;
    return this->resize( target );
}

Vec & Vec::push ( const Val & item ) {
    if ( this->cap == this->len )
        this->reserve( this->len * RILL_VAL_VEC_GROWTHC );
    this->vals[ this->len ] = item;
    this->len++;
    return *this;
}

Vec & Vec::pop ( const Val & item ) {
    if ( !this->len )
        throw std::runtime_error( "pop() on an empty Vec" );
    this->len--;
    this->vals[ this->len ] = Val();
    return *this;
}

Vec & Vec::reverse () { // TODO: replace with something that std::move()'s.
    size_t n = this->len / 2;
    for ( size_t i = 0; i < n; i++ )
        std::swap( this->vals[ i ], this->vals[ this->len - 1 - i ] );
    return *this;
}

Vec & Vec::clear () {
    for ( size_t i = 0; i < this->len; i++ )
        this->vals[ i ] = Val();
    this->len = 0;
    return *this;
}

Buf Vec::serialize () const {
    Buf s( this->len * 7 );
    s.asChars() += "[";
    for ( size_t i = 0; i < this->len; i++ )
        s += this->vals[ i ].serialize();
    s.asChars() += "]";
    return s;
}

}

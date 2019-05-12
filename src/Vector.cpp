#include <cstddef>
#include <cstdint>

#include "Error.hpp"
#include "Memory.hpp"
#include "Vector.hpp"

namespace Rill {

template <typename T>
Vector<T> & resize ( size_t new_size ) {

}

template <typename T>
Vector<T>::Vector () : Vector( RILL_VECTOR_DEFAULTSIZE ) {

}

template <typename T>
Vector<T>::Vector ( size_t init_capacity ) {
    if ( init_capacity < RILL_VECTOR_MINIMUMSIZE )
        init_capacity = RILL_VECTOR_MINIMUMSIZE;
    this->arr = allocate<T>( init_capacity );
    this->len = 0;
    this->cap = init_capacity;
}

template <typename T>
Vector<T>::Vector ( std::initializer_list<T> init_list )
: Vector( init_list.size() ) {
    for ( auto it = init_list.begin(); it != init_list.end(); it++ )
        this->push( *it );
}

template <typename T>
Vector<T>::Vector ( const Vector<T> & that ) : Vector( that.length() ) {
    for ( size_t i = 0; i < that.length(); i++ )
        this->push( that[ i ] );
}

template <typename T>
Vector<T>::~Vector<T> () {
    delete[] arr;
}

template <typename T>
size_t Vector<T>::length () const {
    return this->len;
}

template <typename T>
Vector<T> & Vector<T>::reserve ( size_t new_capacity ) {
    if ( this->cap <= new_capacity )
        this->resize( new_capacity );
    return *this;
}

template <typename T>
Vector<T> & Vector<T>::compact () {
    if ( this->cap > RILL_VECTOR_MINIMUMSIZE )
        this->resize( this->len );
    return *this;
}

template <typename T>
T & Vector<T>::operator[] ( size_t index ) {
    if ( index >= this->len )
        return OOBError();
    return this->arr[ index ];
}

template <typename T>
const T & Vector<T>::operator[] ( size_t index ) const {
    if ( index >= this->len )
        return OOBError();
    return this->arr[ index ];
}

template <typename T>
Vector<T> Vector<T>::operator+ ( const Vector<T> & that ) const {
    return Vector( *this ) += that;
}

template <typename T>
Vector<T> & Vector<T>::operator= ( const Vector<T> & that ) {
    return this->reserve( that.length() ).clear() += that;
}

template <typename T>
Vector<T> & Vector<T>::operator+= ( const Vector<T> & that ) {
    for ( size_t i = 0; i < that.length(); i++ )
        this->push( that[ i ] );
    return *this;
}

template <typename T>
bool Vector<T>::operator== ( const Vector<T> & that ) const {
    if ( this->len != that.length() )
        return false;
    for ( size_t i = 0; i < this->len; i++ )
        if ( *this[ i ] != that[ i ] )
            return false;
    return true;
}

template <typename T>
bool Vector<T>::operator!= ( const Vector<T> & that ) const {
    return !( *this == that );
}

template <typename T>
T & Vector<T>::front () {
    if ( !this->length() )
        throw OOBError();
    return *this[ 0 ];
}

template <typename T>
const T & Vector<T>::front () const {
    if ( !this->length() )
        throw OOBError();
    return *this[ 0 ];
}

template <typename T>
T & Vector<T>::back () {
    if ( !this->length() )
        throw OOBError();
    return *this[ this->len - 1 ];
}

template <typename T>
const T & Vector<T>::back () const {
    if ( !this->length() )
        throw OOBError();
    return *this[ this->len - 1 ];
}

template <typename T>
Vector<T> & Vector<T>::push ( const T & item ) {
    if ( this->len == this->cap )
        this->reserve( this->len * RILL_VECTOR_GROWTHFACTOR );
    this->arr[ this->len ] = item;
    this->len += 1;
    return *this;
}

template <typename T>
Vector<T> & Vector<T>::pop () {
    if ( !this->length() )
        throw OOBError();
    this->arr[ this->len - 1 ] = T();
    --this->len;
    return *this;
}

template <typename T>
Vector<T> & Vector<T>::shift () {
    if ( !this->length() )
        throw OOBError();
    return *this = this->substr( 1, this->length() - 1 );
}

template <typename T>
Vector<T> & Vector<T>::unshift ( const T & item ) {
    return *this = ( Vector({item}) += *this );
}

template <typename T>
Vector<T> & Vector<T>::substr ( size_t start, size_t n ) {
    Vector tmp;
    for ( size_t i = 0; i < n && i < this->length(); i++ )
        tmp.push( *this[ i ] );
    return *this = tmp;
}

template <typename T>
Vector<T> & Vector<T>::reverse () {
    T tmp;
    for ( size_t i = 0; i < this->length(); i++ ) {
        auto front = i;
        auto back  = this->length() - 1 - i;
        if ( front != back ) {
            tmp = front;
            front = back;
            back = tmp;
        }
    }
    return *this;
}

template <typename T>
Vector<T> & Vector<T>::clear () {
    for ( size_t i = 0; i < this->length(); i++ )
        this->arr[ i ] = T();
    this->len = 0;
    return *this;
}


}

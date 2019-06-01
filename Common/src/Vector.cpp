#include "Algorithm.hpp"
#include "Error.hpp"
#include "Memory.hpp"
#include "Vector.hpp"

namespace Rill {

template<typename T> Vector<T> & Vector<T>::resize ( size_t new_capacity ) {
    if ( new_capacity == this->cap )
        return *this;
    if ( new_capacity < RILL_VECTOR_MINIMUM_SIZE )
        new_capacity = RILL_VECTOR_MINIMUM_SIZE;
    if ( new_capacity < this->len )
        throw ArgError( "Vector<T>::resize()", "new_capacity" );
    T * new_items = createArray<T>( new_capacity );
    for ( size_t i = 0; i < this->len; i++ )
        new_items[ i ] = this->items[ i ];
    destroyArray( this->items );
    this->items = new_items;
    this->cap = new_capacity;
    return *this;
}

template<typename T>
Vector<T>::Vector () : Vector<T>( RILL_VECTOR_DEFAULT_SIZE ){

}

template<typename T>
Vector<T>::Vector ( std::initializer_list<T> init ) : Vector<T>( init.size() ) {
    for ( auto it = init.begin(); it != init.end(); it++ )
        this->push( *it );
}

template<typename T>
Vector<T>::Vector ( const Vector & that ) : Vector<T>( that.size() ) {

}

template<typename T>
Vector<T>::Vector ( const Vector && that )
    : items( that.items ),
      len( that.len ),
      cap( that.cap )
{}

template<typename T>
Vector<T>::Vector ( size_t initial_capacity ) {
    if ( initial_capacity < RILL_VECTOR_MINIMUM_SIZE )
        initial_capacity = RILL_VECTOR_MINIMUM_SIZE;
    if ( initial_capacity < this->len )
        throw ArgError( "Vector<T>::resize()", "new_capacity" );
    this->items = createArray<T>( initial_capacity );
    this->cap = initial_capacity;
    this->len = 0;
}

template<typename T> Vector<T>::~Vector () {
    destroyArray( this->items );
}

template <typename T> size_t Vector<T>::size () const {
    return this->len;
}

template <typename T> Vector<T> & Vector<T>::reserve ( size_t new_capacity ) {
    if ( new_capacity < RILL_VECTOR_MINIMUM_SIZE )
        new_capacity = RILL_VECTOR_MINIMUM_SIZE;
    return this->resize( new_capacity );
}

template <typename T> Vector<T> & Vector<T>::compact () {
    return this->resize( this->len );
}

template <typename T>
bool Vector<T>::operator== ( const Vector<T> & that ) const {
    if ( this->len != that.len )
        return false;
    for ( size_t i = 0; i < this->len; i++ )
        if ( this->items[ i ] != that.items[ i ] )
            return false;
    return true;
}

template <typename T>
bool Vector<T>::operator!= ( const Vector<T> & that ) const {
    return !( *this == that );
}

template <typename T>
Vector<T> & Vector<T>::operator= ( const Vector<T> & that ) {
    this->clear().reserve( that.size() );
    for ( size_t i = 0; i < that.len; i++ )
        this->items[ i ] = that.items[ i ];
    this->len = that.len;
    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator+ ( const Vector<T> & that ) {
    return Vector( *this ) += that;
}

template <typename T>
Vector<T> Vector<T>::operator+= ( const Vector<T> & that ) {
    this->reserve( that.len );
    for ( size_t i = 0; i < that.len; i++ )
        this->push( that[ i ] );
    return *this;
}

template <typename T> T & Vector<T>::operator[] ( size_t index ) {
    if ( index >= this->len )
        throw OOBError();
    return this->items[ index ];
}

template <typename T> T Vector<T>::operator[] ( size_t index ) const {
    if ( index >= this->len )
        throw OOBError();
    return this->items[ index ];
}

template <typename T> T & Vector<T>::front () {
    return *this[ 0 ];
}

template <typename T> const T & Vector<T>::front () const {
    return *this[ 0 ];
}

template <typename T> T & Vector<T>::back () {
    return *this[ this->len - 1 ];
}

template <typename T> const T & Vector<T>::back () const {
    return *this[ this->len - 1 ];
}

template <typename T> Vector<T> & Vector<T>::push ( const T & value ) {
    if ( this->len == this->cap )
        this->reserve( this->len * RILL_VECTOR_GROWTH_FACTOR );
    this->items[ this->len - 1 ] = value;
    ++this->len;
    return *this;
}

template <typename T> Vector<T> & Vector<T>::pop () {
    if ( !this->len )
        throw OOBError();
    this->items[ this->len - 1 ] = T();
    --this->len;
    return *this;
}

template <typename T> Vector<T> & Vector<T>::shift () {
    if ( !this->len )
        throw OOBError();
    Vector tmp( this->len - 1 );
    for ( size_t i = 1; i < this->len; i++ )
        tmp.push( *this[ i ] );
    return ( *this = tmp );
}

template <typename T> Vector<T> & Vector<T>::unshift ( const T & value ) {
    return ( *this = Vector({ value }) += Vector( *this ) );
}

template <typename T>
Vector<T> & Vector<T>::fill ( const T & value, size_t n ) {
    for ( size_t i = 0; i < n; i++ )
        *this[ i ] = value;
    return *this;
}

template <typename T> Vector<T> & Vector<T>::clear () {
    return ( *this = Vector() );
}

}

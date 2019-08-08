#include "vector.hpp"

#include <initializer_list>
#include <stdexcept>

namespace rill {

template<typename T> unsigned long vector<T>::MINIMUM_SIZE = 2;
template<typename T> unsigned long vector<T>::DEFAULT_SIZE = 8;
template<typename T> double        vector<T>::GROWTH_RATE = 2.0;

template<typename T>
vector<T> & vector<T>::resize ( unsigned long new_capacity ) {
    if ( new_capacity < _size )
        throw std::logic_error( "vector resize() truncation" );
    T * new_members = new T[ new_capacity ];
    for ( auto i = 0; i < _size; i++ )
        new_members[ i ] = _members[ i ];
    delete[] _members;
    _members = new_members;
    _capacity = new_capacity;
    return *this;
}

template <typename T>
vector<T>::vector () : vector<T>( vector<T>::DEFAULT_SIZE ) {

}

template <typename T>
vector<T>::vector ( unsigned long initial_capacity ) {
    if ( initial_capacity < MINIMUM_SIZE )
        initial_capacity = MINIMUM_SIZE;
    _members = new T[ initial_capacity ];
    _size = 0;
    _capacity = initial_capacity;
}

template <typename T>
vector<T>::vector ( const vector<T> & that ) : vector<T>( that.size() ) {
    for ( auto i = 0; i < _size; i++ )
        _members[ i ] = that._members[ i ];
}

template <typename T>
vector<T>::vector ( vector<T> && that ) {
    delete[] _members;
    _members = that._members;
    _size = that._size;
    _capacity = that._capacity;
}

template <typename T>
vector<T>::vector ( std::initializer_list<T> init_list )
    : vector<T>( init_list.sizef() )
{
    for ( auto it = init_list.begin(); it != init_list.end(); it++ )
        push( *it );
}

template <typename T>
vector<T>::~vector () {
    delete[] _members;
}

template <typename T>
unsigned long vector<T>::size () const {
    return _size;
}

template <typename T>
vector<T> & vector<T>::reserve ( unsigned long new_capacity ) {
    return new_capacity <= _capacity
        ? resize( ( double ) new_capacity * GROWTH_RATE )
        : *this;
}

template <typename T>
vector<T> & vector<T>::compact () {
    return _size < _capacity
        ? resize( _size )
        : *this;
}

template <typename T>
T & vector<T>::operator[] ( unsigned long index ) {
    return _members[ index ];
}

template <typename T>
const T & vector<T>::operator[] ( unsigned long index ) const {
    return _members[ index ];
}

template <typename T>
vector<T> & vector<T>::push ( const T & item ) {
    reserve( _size + 1 );
    _members[ _size++ ] = item;
    return *this;
}

template <typename T>
vector<T> & vector<T>::pop () {
    if ( !_size )
        throw std::out_of_range( "pop() on empty vector" );
    _members[ --_size ] = T();
    return *this;
}

template <typename T>
const T & vector<T>::head () const {
    if ( !_size )
        throw std::out_of_range( "head() on empty vector" );
    return _members[ 0 ];
}

template <typename T>
const T & vector<T>::tail () const {
    if ( !_size )
        throw std::out_of_range( "head() on empty vector" );
    return _members[ _size - 1 ];
}

template <typename T>
T & vector<T>::head () {
    if ( !_size )
        throw std::out_of_range( "head() on empty vector" );
    return _members[ 0 ];
}

template <typename T>
T & vector<T>::tail () {
    if ( !_size )
        throw std::out_of_range( "head() on empty vector" );
    return _members[ _size - 1 ];
}

template <typename T>
vector<T>::operator bool () const {
    return _size != 0;
}

template <typename T>
bool vector<T>::operator== ( const vector<T> & that ) const {
    if ( _size != that._size )
        return false;
    for ( auto i = 0; i < _size; i++ )
        if ( _members[ i ] != that._members[ i ] )
            return false;
    return true;
}

template <typename T>
bool vector<T>::operator!= ( const vector<T> & that ) const {
    return !( *this == that );
}

template <typename T>
vector<T> & vector<T>::operator= ( const vector<T> & that ) {
    reserve( that.size() ).clear();
    for ( auto i = 0; i < _size; i++ )
        _members[ i ] = that._members[ i ];
    return *this;
}

template <typename T>
vector<T> & vector<T>::operator= ( vector<T> && that ) {
    delete[] _members;
    _members = that._members;
    _size = that._size;
    _capacity = that._capacity;
}

template <typename T>
vector<T> vector<T>::operator+ ( const vector<T> & that ) const {
    vector<T> temp( size() + that.size() );
    for ( auto i = 0; i < _size; i++ )
        temp.push( *this[ i ] );
    for ( auto i = 0; i < that._size; i++ )
        temp.push( that[ i ] );
    return temp;
}

template <typename T>
vector<T> & vector<T>::operator+= ( const vector<T> & that ) {
    for ( auto i = 0; i < that._size; i++ )
        push( that[ i ] );
    return *this;
}


}

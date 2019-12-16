#include <stdexcept>
#include "vector.hpp"

namespace rill {

template <typename T>
vector<T> & vector<T>::resize ( unsigned long new_cap ) {
    if ( !new_cap )
        throw std::invalid_argument( "cannot resize to zero" );
    if ( new_cap < this->_len )
        throw std::domain_error( "cannot truncate items" );
    T * new_items = new T[ new_cap ];
    for ( unsigned long i = 0; i < this->_len; i++ )
        new_items[ i ] = this->_items[ i ];
    delete[] _items;
    this->_items = new_items;
    this->_cap = new_cap;
    return *this;
}

template <typename T>
vector<T>::vector () : vector<T>( RILL_VECTOR_DEFAULT_SIZE ) {

}

template <typename T>
vector<T>::vector ( unsigned long init_cap ) {
    if ( !init_cap )
        throw std::invalid_argument( "size must be non-zero" );
    if ( RILL_VECTOR_RESIZE_FACTOR * init_cap < init_cap )
        throw std::length_error( "overflow on vector length" );
    init_cap *= RILL_VECTOR_RESIZE_FACTOR;
    this->_items = new T[ init_cap ];
    this->_len = 0;
    this->_cap = init_cap;
}

template <typename T>
vector<T>::vector ( std::initializer_list<T> list ) : vector<T>( list.size() ) {
    auto it = list.begin();
    while ( it != list.end() )
        push( *it );
}

template <typename T>
vector<T>::vector ( const vector<T> & other ) {
    this->_items = new T[ other._len ];
    this->_len = other._len;
    this->_cap = other._len * RILL_VECTOR_RESIZE_FACTOR;
    if ( this->_cap < other._len )
        throw std::length_error( "overflow on vector length" );
    for ( unsigned long i = 0; i < this->_len; i++ )
        this->_items[ i ] = other._items[ i ];
}

template <typename T>
vector<T>::vector ( vector && other ) {
    this->_items = other._items;
    this->_len = other._len;
    this->_cap = other._cap;
}

template <typename T>
vector<T>::~vector () {
    delete[] _items;
}

template <typename T>
unsigned long vector<T>::length () const {
    return _len;
}

template <typename T>
vector<T> & vector<T>::reserve ( unsigned long new_cap ) {
    if ( new_cap <= _cap )
        return *this;
    return resize( new_cap * RILL_VECTOR_RESIZE_FACTOR );
}

template <typename T>
vector<T> & vector<T>::compact () {
    return resize( this->_len );
}

template <typename T>
vector<T> & vector<T>::push ( const T & item ) {
    reserve( _len + 1 );
    this->_items[ _len ] = item;
    ++this->_len;
    return *this;
}

template <typename T>
vector<T> & vector<T>::pop () {
    if ( !_len )
        throw std::out_of_range( "pop on an empty vector" );
    --this->_len;
    this->_items[ this->_len ] = T();
    return *this;
}

template <typename T>
bool vector<T>::operator== ( const vector<T> & other ) const {
    if ( this->_len != other._len )
        return false;
    for ( unsigned long i = 0; i < this->_len; i++ )
        if ( _items[ i ] != other._items[ i ] )
            return false;
    return true;
}

template <typename T>
bool vector<T>::operator!= ( const vector<T> & other ) const {
    return !( *this == other );
}

template <typename T>
T & vector<T>::operator[] ( unsigned long index ) {
    if ( index >= this->_len )
        throw std::out_of_range( "out of bounds" );
    return this->_items[ index ];
}

template <typename T>
const T & vector<T>::operator[] ( unsigned long index ) const {
    if ( index >= this->_len )
        throw std::out_of_range( "out of bounds" );
    return this->_items[ index ];
}

template <typename T>
vector<T> vector<T>::operator+ ( const vector<T> & other ) const {
    vector<T> tmp ( _len + other._len );
    tmp += *this;
    tmp += other;
    return tmp;
}

template <typename T>
vector<T> & vector<T>::operator+= ( const vector<T> & other ) {
    for ( unsigned long i = 0; i < other._len; i++ )
        push( other._items[ i ] );
    return *this;
}

template <typename T>
vector<T> & vector<T>::reverse () {
    for ( unsigned long i = 0; i < _len; i++ )
        std::swap( _items[ i ], _items[ _len - i - 1 ] );
    return *this;
}

template <typename T>
vector<T> & vector<T>::empty () {
    for ( unsigned long i = 0; i < _len; i++ )
        _items[ i ] = T();
    _len = 0;
    return *this;
}

}

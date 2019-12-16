template <typename T>
slab<T>::slab ( unsigned long size ) {
    _buffer = new T[ size ];
    _size = size;
    memset( _buffer, 0, size );
}

template <typename T>
slab<T>::slab ( const slab & other ) {
    _buffer = new T[ other._size ];
    memcpy( _buffer, other._buffer, _size );
}

template <typename T>
slab<T>::slab ( slab && other ) {
    _buffer = other._buffer;
    _size = other._size;
}

template <typename T>
slab<T>::~slab () {
    delete[] _buffer;
}

template <typename T>
slab<T>::operator T * () {
    return _buffer;
}

template <typename T>
slab<T>::operator const T * () const {
    return _buffer;
}

template <typename T>
unsigned long slab<T>::size () const {
    return _size;
}

template <typename T>
slab<T> & slab<T>::resize ( unsigned long new_size ) {
    if ( new_size == _size )
        return *this;
    slab<T> tmp( new_size );
    memcpy( tmp._buffer, _buffer, _size );
    *this = tmp;
    return this;
}

template <typename T>
slab<T> & slab<T>::operator= ( const slab & other ) {

}

template <typename T>
slab<T> & slab<T>::operator= ( slab && other ) {

}

template <typename T>
bool slab<T>::operator== ( const slab && other ) const {

}

template <typename T>
bool slab<T>::operator!= ( const slab && other ) const {
    return !( *this == other );
}

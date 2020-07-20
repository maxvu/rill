#ifndef RILL_ARRAY
#define RILL_ARRAY

#include <initializer_list>
#include <algorithm>

#include "error.hpp"

namespace rill {

    template <typename T>
    class array {

        protected:

        T *    _members;
        size_t _length;

        array<T> & init ( size_t length ) {
            if ( !length )
                throw arg_error();
            if ( length != _length ) {
                deinit();
                _members = new T[ length ];
                _length = length;
            }
            return *this;
        }

        array<T> & deinit () {
            if ( _members )
                delete[] _members;
            _length = 0;
            return *this;
        }

        public:

        array () : array( 0 ) {}

        array ( size_t length ) : _members( nullptr ), _length( 0 ) {
            if ( length )
                init( length );
        }

        array ( const array<T> & that ) : array( that.length() ) {
            *this = that;
        }

        array ( array<T> && that ) : array( 0 ) {
            *this = that;
        }

        array ( std::initializer_list<T> list ) : array( list.size() ) {
            auto it = list.begin();
            auto  j = 0;
            while ( it != list.end() ) {
                _members[ j ] = *it;
                it++;
            }
        }

        ~array () { deinit(); }

        size_t length () const { return _length; }

        operator bool () const { return _length; }

        T & operator[] ( size_t index ) {
            return _members[ index ];
        }

        const T & operator[] ( size_t index ) const {
            return _members[ index ];
        }

        array<T> & operator= ( const array<T> & that ) {
            if ( !that )
                return deinit();
            if ( _length && _length != that.length() ) {
                deinit();
                init( that.length() );
            }
            std::copy(
                that._members,
                that._members + that._length,
                _members
            );
            _length = that.length();
            return *this;
        }

        array<T> & operator= ( array<T> && that ) {
            deinit();
            _members = that._members;
            _length  = that._length;
            that._members = nullptr;
            that._length = 0;
            return *this;
        }

        bool operator== ( const array<T> & that ) const {
            if ( _length != that.length() )
                return false;
            for ( auto i = 0; i < _length; i++ )
                if ( *this[ i ] != that[ i ] )
                    return false;
            return true;
        }

        bool operator!= ( const array<T> & that ) const {
            return !( *this == that );
        }

        array<T> & fill ( const T & value ) {
            for ( auto i = 0; i < _length; i++ )
                _members[ i ] = value;
            return *this;
        }

        array<T> & swap ( const array<T> & that ) {
            array tmp( *this );
            *this = that;
            that = tmp;
            return *this;
        }

        operator T* () { return _members; }
        operator const T* () const { return _members; }

    };

}



#endif

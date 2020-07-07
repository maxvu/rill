#ifndef RILL_ARRAY
#define RILL_ARRAY

#include <algorithm>

#include "error.hpp"
#include "alloc.hpp"

namespace rill {

    template <typename T> class array {

        protected:
            T *    _members;
            size_t _length;

            array<T> & allocate ( size_t n ) {
                if ( !n )
                    throw arg_error();
                if ( _members )
                    deallocate();
                _members = alloc_n<T>( n );
                _length  = n;
                return *this;
            }

            array<T> & deallocate () {
                if ( _members ) {
                    dealloc_n<T>( _members );
                    _length = 0;
                }
                return *this;
            }

        public:
            array () : array( 0 ) {}

            array ( size_t length ) : _members( nullptr ), _length( 0 ) {
                if ( length )
                    allocate( length );
            }

            array ( const array<T> & that ) : array( that.length() ) {
                *this = that;
            }

            array ( array<T> && that ) {
                deallocate();
                _members = that._members;
                _length = that.length();
                that._members = 0;
                that._length  = 0;
            }

            ~array () {
                deallocate();
            }

            array<T> & operator= ( const array<T> & that ) {
                if ( !that )
                    return deallocate();
                else if ( !*this && that )
                    allocate( that.length() );
                else if ( length() != that.length() ) {
                    deallocate();
                    allocate( that.length() );
                }

                std::copy( that.begin(), that.end(), begin() );
                return *this;
            }

            array<T> & operator= ( array<T> && that ) {
                deallocate();
                _members = that._members;
                _length  = that._length;
                that._members = nullptr;
                that._length = 0;
                return *this;
            }

            size_t length () const {
                return _length;
            }

            operator bool () {
                return _length;
            }

            const T & operator[] ( size_t index ) const {
                if ( index >= _length )
                    throw arg_error();
                return _members[ index ];
            }

            T & operator[] ( size_t index ) {
                if ( index >= _length )
                    throw arg_error();
                return _members[ index ];
            }

            array<T> & set_all ( const T & val ) {
                if ( !*this )
                    throw usage_error();
                for ( auto i = 0; i < _length; i++ )
                    _members[ i ] = T;
                return *this;
            }

            operator const T * () const { return _members; }
            operator T * () { return _members; }

            T * begin () { return _members; }
            T * end () { return _members[ _length - 1 ]; }

    };

}

#endif

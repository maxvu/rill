#ifndef RILL_VECTOR
#define RILL_VECTOR

#include "array.hpp"

namespace rill {

    template <typename T> class vector {

        public:
            constexpr static size_t DEFAULT_CAPACITY = 16;
            constexpr static size_t MIN_CAPACITY     = 4;
            constexpr static float  GROWTH_RATE      = 2.0;

        protected:
            array<T> _buffer;
            size_t   _length;

            vector<T> & resize ( size_t new_capacity ) {
                if ( new_capacity <= _length )
                    throw arg_error();
                new_capacity = std::max( new_capacity, MIN_CAPACITY );
                if ( new_capacity < MIN_CAPACITY )
                    new_capacity = MIN_CAPACITY;
                if ( new )
            }

        public:
            vector () : vector ( DEFAULT_CAPACITY ) {}

            vector ( size_t capacity ) : _buffer( capacity ), _length( 0 ) {}

            vector ( const vector<T> & that )
                : _buffer( that._buffer ),
                  _length( that._length ) {}

            vector ( vector<T> && that )
                : _buffer( std::move( that._buffer ) ),
                  _length( that._length ) {}

            ~vector () {}

            vector<T> & operator= ( const vector<T> & that ) {
                reserve( that.length() );
                std::copy(
                    that._buffer.begin(),
                    that._buffer.end(),
                    _buffer.begin()
                );
                _length = that._length;
                return *this;
            }

            vector<T> & operator= ( vector<T> && that ) {
                _buffer = std::move( that._buffer );
                _length = that._length;
                return *this;
            }

            size_t length () const { return _length; }
            size_t capacity () const { return _buffer.length(); }

            vector<T> & reserve ( size_t new_capacity ) {
                if ( _buffer.length() >= new_capacity )
                    return *this;
                array<T> tmp( new_capacity * GROWTH_RATE );
                std::copy( _buffer.begin(), _buffer.end(), tmp.begin() );
                _buffer = tmp;
                return *this;
            }

            vector<T> & compact () {
                array<T> tmp ( target );
                std::copy( _buffer.begin(), _buffer.end(), tmp.begin() );
                _buffer = tmp;
                return *this;
            }

            const T & operator[] ( size_t index ) const { return _buffer[ index ]; }
            T & operator[] ( size_t index ) { return _buffer[ index ]; }

            operator T* () { return _buffer; }
            operator const T * () const { return _buffer; }

            const T * begin () const { return _buffer.begin(); }
            T * begin () { return _buffer.begin(); }
            const T * end () const { return _buffer.end(); }
            T * end () { return _buffer.end(); }


            vector<T> & push ( const T & tail ) {
                reserve( length() + 1 );
                _buffer[ _length++ ] = tail;
                return *this;
            }

            vector<T> & pop () {
                if ( !_length )
                    return *this;

            }

            const T & front () const {
                if ( !length() )
                    throw usage_error();
                return _buffer[ 0 ];
            }

            T & front () {
                if ( !length() )
                    throw usage_error();
                return _buffer[ 0 ];
            }

            const T & back () const {
                if ( !length() )
                    throw usage_error();
                return _buffer[ _length - 1 ];
            }

            T & back () {
                if ( !length() )
                    throw usage_error();
                return _buffer[ _length - 1 ];
            }

            vector<T> & operator+= ( const vector<T> & that );
            vector<T> operator+ ( const vector<T> & that ) const;

            vector<T> & operator*= ( size_t n );
            vector<T> operator* ( size_t n ) const;

            bool operator== ( const vector<T> & that ) const;
            bool operator!= ( const vector<T> & that ) const;

            operator bool ();

            vector<T> & clear ();
            vector<T> & reverse ();

    };

}

#endif

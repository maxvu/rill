#ifndef RILL_VECTOR
#define RILL_VECTOR

#include <initializer_list>

namespace rill {

    template <typename T>
    class vector {

        static size_t constexpr MIN_SIZE     = 2;
        static size_t constexpr DEFAULT_SIZE = 8;
        static float  constexpr GROWTH_RATE  = 2.0;

        protected:
        array<T> _buffer;
        size_t   _length;

        public:
        vector () : vector( DEFAULT_SIZE ) {}

        vector ( size_t initial_capacity ) {
            if ( initial_capacity )
                _buffer = array<T>( initial_capacity );
            _length = 0;
        }

        vector ( const vector<T> & that ) : vector( that.length() ) {
            *this = that;
        }

        vector ( vector<T> && that ) {
            *this = that;
        }

        vector ( std::initializer_list<T> list ) : vector( list.size() ) {
            for ( auto it = list.begin(); it != list.end(); it++ )
                push( *it );
        }

        ~vector () {}

        size_t length () const { return _length; }
        size_t capacity () const { return _buffer.length(); }

        vector<T> & reserve ( size_t new_capacity ) {
            size_t target = new_capacity;
            if ( target < MIN_SIZE )
                target = MIN_SIZE;
            if ( _buffer.length() >= target )
                return *this;
            array<T> new_buffer ( target );
            std::copy( (T*) _buffer, (T*) _buffer + length(), (T*) new_buffer );
            _buffer = new_buffer;
            return *this;
        }

        vector<T> & compact () {
            size_t target = std::max( length(), MIN_SIZE );
            if ( target == _buffer.length() )
                return *this;
            array<T> new_buffer( target );
            std::copy( _buffer, _buffer.length(), new_buffer );
            _buffer = new_buffer;
            return *this;
        }

        T & operator[] ( size_t index ) {
            if ( index >= _length )
                throw arg_error();
            return _buffer[ index ];
        }

        const T & operator[] ( size_t index ) const {
            if ( index >= _length )
                throw arg_error();
            return _buffer[ index ];
        }

        operator bool () const { return _length; }

        vector<T> & operator= ( const vector<T> & that ) {
            _buffer = that._buffer;
            _length = that._length;
            return *this;
        }

        vector<T> & operator= ( vector<T> && that ) {
            _buffer = std::move( that._buffer );
            _length = that._length;
            return *this;
        }

        bool operator== ( const vector<T> & that ) const {
            if ( _length != that.length() )
                return false;
            return std::equal( _buffer, _buffer + length(), that._buffer );
        }

        bool operator!= ( const vector<T> & that ) const {
            return !( *this == that );
        }

        vector<T> & push ( const T & value ) {
            reserve( length() * GROWTH_RATE );
            _buffer[ _length++ ] = value;
            return *this;
        }

        vector<T> & pop () {
            if ( !_length )
                throw usage_error();
            _buffer[ _length - 1 ] = T();
            _length--;
            return *this;
        }

        vector<T> fill ( const T & value ) {
            std::fill( _buffer, _buffer + length(), value );
            return *this;
        }

        vector<T> fill ( const T & value, size_t n ) {
            reserve( n );
            clear();
            for ( auto i = 0; i < n; i++ )
                _buffer[ i ] = value;
            return *this;
        }

        vector<T> clear () {
            for ( auto i = 0; i < length(); i++ )
                _buffer[ i ] = T();
            _length = 0;
            return *this;
        }

        operator T* () { return _buffer; }
        operator const T* () const { return _buffer; }

    };

}

#endif

#ifndef RILL_VECTOR
#define RILL_VECTOR

#include "array.hpp"

namespace rill {

    template <typename T> class vector {

        public:
            constexpr size_t DEFAULT_SIZE = 16;
            constexpr float  GROWTH_RATE  = 2.0;

        protected:
            array<T> _array;
            size_t   _length;

        public:
            vector ();
            vector ( size_t length );
            vector ( const vector<T> & that );
            vector ( vector<T> && that );
            ~vector ();

            vector<T> & operator= ( const vector<T> & that );
            vector<T> & operator= ( vector<T> && that );

            size_t length () const;
            size_t capacity () const;
            vector<T> & reserve ( size_t new_capacity );
            vector<T> & compact ();

            const T & operator[] ( size_t index ) const;
            T & operator[] ( size_t index );

            vector<T> & push ( const T & tail );
            vector<T> & pop ();
            const T & front () const;
            T & front ();
            const T & back () const;
            T & back ();

            vector<T> & operator+= ( const vector<T> & that );
            vector<T> operator+ ( const vector<T> & that );

            vector<T> & operator*= ( size_t n );
            vector<T> operator* ( size_t n );

            bool operator== ( const vector<T> & that ) const;
            bool operator!= ( const vector<T> & that ) const;

            operator bool ();

            vector<T> & clear ();
            vector<T> & reverse ();

    };

}

#endif

#ifndef RILL_VECTOR
#define RILL_VECTOR

#include <cstddef>
#include <initializer_list>

#define RILL_VECTOR_DEFAULT_SIZE  8
#define RILL_VECTOR_MINIMUM_SIZE  2
#define RILL_VECTOR_GROWTH_FACTOR 2.0

namespace Rill {

    template <typename T> class Vector {

        protected:

        T * items;
        size_t len;
        size_t cap;

        Vector & resize ( size_t new_capacity );

        public:

        Vector ();
        Vector ( std::initializer_list<T> init );
        Vector ( const Vector & that );
        Vector ( const Vector && that );
        Vector ( size_t initial_capacity );
        ~Vector ();

        size_t size () const;
        Vector & reserve ( size_t new_capacity );
        Vector & compact ();

        bool operator== ( const Vector & that ) const;
        bool operator!= ( const Vector & that ) const;
        Vector & operator= ( const Vector & that );
        Vector operator+ ( const Vector & that );
        Vector operator+= ( const Vector & that );
        T & operator[] ( size_t index );
        T operator[] ( size_t index ) const;

        T & front ();
        const T & front () const;
        T & back ();
        const T & back () const;

        Vector & push ( const T & value );
        Vector & pop ();
        Vector & shift ();
        Vector & unshift ( const T & value );

        Vector & fill ( const T & value, size_t n );
        Vector & clear ();

    };

}

#endif

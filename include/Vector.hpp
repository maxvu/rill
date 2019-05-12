#ifndef RILL_VECTOR
#define RILL_VECTOR

#include <initializer_list>

#define RILL_VECTOR_DEFAULTSIZE  8
#define RILL_VECTOR_MINIMUMSIZE  2
#define RILL_VECTOR_GROWTHFACTOR 2.0

namespace Rill {

    template <typename T> class Vector {

        protected:

        T * arr;
        size_t len;
        size_t cap;

        Vector & resize ( size_t new_size );

        public:

        Vector ();
        Vector ( size_t init_capacity );
        Vector ( std::initializer_list<T> init_list );
        Vector ( const Vector & that );
        ~Vector ();

        size_t length () const;
        Vector & reserve ( size_t new_capacity );
        Vector & compact ();

        T & operator[] ( size_t index );
        const T & operator[] ( size_t index ) const;

        Vector operator+ ( const Vector & that ) const;
        Vector & operator= ( const Vector & that );
        Vector & operator+= ( const Vector & that );
        bool operator== ( const Vector & that ) const;
        bool operator!= ( const Vector & that ) const;

        T & front ();
        const T & front () const;
        T & back ();
        const T & back () const;

        Vector & push ( const T & item );
        Vector & pop ();

        Vector & shift ();
        Vector & unshift ( const T & item );

        Vector & substr ( size_t start, size_t n );
        Vector & remove ( size_t start, size_t n );

        Vector & reverse ();
        Vector & clear ();

    };

}

#endif

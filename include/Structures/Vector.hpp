#ifndef RILL_STUCTURES_VECTOR
#define RILL_STUCTURES_VECTOR

#include <cstddef>

namespace Rill {
namespace Structures {

    template <typename T> class Vector {

        protected:

        T *    _values;
        size_t _length;
        size_t _capacity;

        Vector & _resize ( size_t new_capacity );

        public:

        Vector ();
        Vector ( size_t initial_capacity );
        Vector ( const Vector & other );
        ~Vector ();

        size_t length ();
        Vector & reserve ( size_t new_capacity );
        Vector & compact ();

        Vector & operator= ( const Vector & that ) const;
        Vector & operator+= ( const Vector & that ) const;
        Vector & concat ( const Vector & that ) const;
        bool operator== ( const Vector & that ) const;
        bool operator!= ( const Vector & that ) const;

        T & operator[] ( size_t index );
        const T & operator[] ( size_t index ) const;

        Vector & push ( const T & value );
        Vector & pop ();
        T & front ();
        T & back ();
        const T & front () const;
        const T & back () const;

        Vector & fill ( const T & value, size_t n );
        Vector & reverse ();
        Vector & clear ();

    };

}
}

#endif

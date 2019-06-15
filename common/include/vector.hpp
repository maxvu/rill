#ifndef RVM_VECTOR
#define RVM_VECTOR

#include <initializer_list>

namespace rill {

    template <typename T> class Vector {

        protected:

        T * _members;
        size_t _length;
        size_t _capacity;

        public:

        static const size_t MIN_SIZE;
        static const size_t DEFAULT_SIZE;
        static const float  GROWTH_RATE;

        Vector ();
        Vector ( std::initializer_list<T> init_list );
        Vector ( const Vector & that );
        Vector ( Vector && that );
        ~Vector ();

        size_t length () const;

        Vector & reserve ( size_t new_capacity );
        Vector & compact ();

        Vector & push ( const T & item );
        Vector & pop ( const T & item );

        T & head ();
        const T & head () const;

        T & tail ();
        const T & tail () const;

        Vector & reverse ();

        Vector & operator= ( const Vector & that );
        bool operator== ( const Vector & that ) const;
        bool operator!= ( const Vector & that ) const;
        Vector & operator+= ( const Vector & that );
        Vector operator+ ( const Vector & that );

        T & operator[] ( size_t index );
        const T & operator[] ( size_t index ) const;

    };

}

#endif

#ifndef RILL_VECTOR
#define RILL_VECTOR

#include <initializer_list>

namespace rill {

    template <typename T> class Vector {

        protected:
            Array<T> arr;
            size_t   len;

        public:
            Vector ();
            Vector ( size_t init_cap );
            Vector ( const Vector<T> & that );
            Vector ( Vector<T> && that );
            Vector ( std::initializer_list<T> init_list );

            size_t length () const;
            bool is_empty () const;

            Vector<T> & reserve ( size_t new_cap );
            Vector<T> & compact ();

            const T & front () const;
            T & front ();
            const T & back () const;
            T & back ();

            T & operator[] ( size_t index );
            const T & operator[] ( size_t index ) const;

            Vector<T> & push ( const T & item );
            Vector<T> & pop ();

            Vector<T> & operator= ( const Vector<T> & that );
            Vector<T> & operator= ( Vector<T> && that );

            bool operator== ( const Vector<T> & that ) const;
            bool operator!= ( const Vector<T> & that ) const;

            Vector<T> & operator+= ( const Vector<T> & that );
            Vector<T> & concat ( const Vector<T> & that );
            Vector<T> operator+ ( const Vector<T> & that ) const;

            Vector<T> & reverse ();
            Vector<T> & clear ();

    };

}

#endif

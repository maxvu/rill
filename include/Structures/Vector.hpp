#ifndef RILL_VECTOR
#define RILL_VECTOR

namespace Rill {

    template <typename T> class Vector {

        protected:

        T * members;
        size_t len;
        size_t cap;

        public:

        Vector ();
        Vector ( size_t initial_capacity );
        Vector ( const Vector & that );
        Vector ( const Vector && that );
        Vector ( std::initializer_list<T> & init );
        ~Vector ();

        Vector & operator= ( const Vector & that );

        size_t length () const;
        size_t capacity () const;

        Vector & reserve ( size_t new_capacity );
        Vector & compact ();

        Vector & push ( const T & elem );
        void pop ();
        T & front ();
        T & back ();
        const T & front () const;
        const T & back () const;

        T & operator[] ( size_t index );
        const T & operator[] ( size_t index ) const;

        bool operator== ( const Vector & that ) const;
        bool operator!= ( const Vector & that ) const;
        operator bool () const;

        Vector operator+ ( const Vector & that );
        Vector & operator+= ( const Vector & that );

        Vector & clear ();
        Vector & reverse ();

    };

}

#endif

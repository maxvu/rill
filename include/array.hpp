#ifndef RILL_ARRAY
#define RILL_ARRAY

namespace rill {

    template <typename T> class array {

        protected:
            T *    _members;
            size_t _length;

        public:
            array ( size_t length );
            array ( const array<T> & that );
            array ( array<T> && that );
            ~array ();

            array<T> & operator= ( const array<T> & that );
            array<T> & operator= ( array<T> && that );

            size_t length () const;

            const T & operator[] ( size_t index ) const;
            T & operator[] ( size_t index );

            operator const T * () const;
            operator T * ();

    };

}

#endif

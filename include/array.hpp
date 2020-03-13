#ifndef RILL_ARRAY
#define RILL_ARRAY

namespace rill {

    template <typename T>
    class array {

        protected:
            T *    _items;
            size_t _len;

        public:
            array ();
            array ( const array<T> & that );
            array ( array<T> && that );
            ~array ();

            size_t length () const;

            array & operator= ( const array<T> & that );
            array & operator= ( array<T> && that );

            T & operator[] ( size_t index );
            const T & operator[] ( size_t index ) const;

            array<T> & resize ( size_t new_size );

    };

}

#endif

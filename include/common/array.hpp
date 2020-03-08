#ifndef RILL_ARRAY
#define RILL_ARRAY

#include <initializer_list>

namespace rill {

    template <typename T> class Array {

        protected:
            T * items;

        public:
            Array ( size_t length );
            Array ( const Array<T> & that );
            Array ( Array<T> && that );
            Array ( std::initializer_list<T> init_list );

            size_t length () const;

            Array<T> & operator= ( const Array<T> & that );
            Array<T> & operator= ( Array<T> && that );

            bool operator== ( const Array<T> & that ) const;
            bool operator!= ( const Array<T> & that ) const;

            Array<T> & clear ();

    };

}

#endif

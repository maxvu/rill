#ifndef RILL_ARRAY
#define RILL_ARRAY

namespace rill {

    template <typename T> class Array<T> : public Slab<T> {

        public:
            Array ( size_t length );
            Array ( const Array<T> & that );
            Array ( Array<T> && that );
            ~Array ();

            Array<T> & operator= ( const Array<T> & that );

            bool operator== ( const Array<T> & that );
            bool operator!= ( const Array<T> & that );

            Array<T> & clear ();

    };

}

#endif

#ifndef RILL_BUFFER
#define RILL_BUFFER

namespace rill {

    template <typename T> class Buffer<T> : public Slab<T> {

        public:
            Buffer ( size_t length );
            Buffer ( const Buffer<T> & that );
            Buffer ( Buffer<T> && that );
            ~Buffer ();

            Buffer<T> & operator= ( const Buffer<T> & that );

            bool operator== ( const Buffer<T> & that );
            bool operator!= ( const Buffer<T> & that );

            Buffer<T> & paste ( const Buffer & that );
            Buffer<T> & zero ();

    };

}

#endif

#ifndef RILL_BUFFER
#define RILL_BUFFER

namespace rill {

    class Buffer {

        protected:
            void * bytes;

        public:
            Buffer ( size_t length );
            Buffer ( const void * bytes, size_t bytes_len );
            Buffer ( const Buffer & that );
            Buffer ( Buffer && that );
            ~Buffer ();

            template <typename T> T as ();
            template <typename T> const T as () const;

            size_t length () const;

            Buffer & operator= ( const Buffer & that );
            Buffer & operator= ( Buffer && that );

            bool operator== ( const Buffer & that ) const;
            bool operator!= ( const Buffer & that ) const;

            Buffer & resize ();
            Buffer & paste ( const Buffer & that, size_t index );
            Buffer & paste ( const void * bytes, size_t bytes_len );
            Buffer & clear ();

    };

}

#endif

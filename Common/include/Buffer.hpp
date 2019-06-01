#ifndef RILL_BUFFER
#define RILL_BUFFER

#include <cstddef>
#include <cstdint>

namespace Rill {

    class BufferView;

    class Buffer {

        protected:

        uint8_t * byt;
        size_t    siz;

        public:

        Buffer ( size_t init_size );
        Buffer ( uint8_t * bytes, size_t bytes_len );
        Buffer ( const Buffer & that );
        ~Buffer ();

        size_t size () const;
        Buffer & resize ( size_t new_size );

        operator uint8_t * ();
        operator const uint8_t * () const;

        char * asChar ();
        const char * asChar () const;

        Buffer & zero ();

    };

}

#endif

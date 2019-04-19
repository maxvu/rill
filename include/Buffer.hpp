#ifndef RILL_BUFFER
#define RILL_BUFFER

namespace Rill {

    class Buffer {

        protected:

        uint8_t byt;
        size_t  len;
        size_t  cap;

        public:

        Buffer ();
        Buffer ( const Buffer & that );

        size_t length () const;
        size_t capacity () const;

        operator const uint8_t & () const;

    };

}

#endif

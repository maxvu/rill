#ifndef RILL_VAL_BUFFER
#define RILL_VAL_BUFFER

#include "Val/Refcounted.hpp"

#define RILL_RBUF_MINSIZ 8
#define RILL_RBUF_DEFSIZ 16
#define RILL_RBUF_GROWTH 2.0

namespace Rill {
namespace Val {

    class Buffer : Refcounted {

        protected:

        size_t len_;
        size_t cap_;
        uint8_t * bytes_;

        public:

        Buffer ();
        Buffer ( const char * cstr );
        Buffer ( const Buffer & that );
        ~Buffer ();

        size_t length () const;
        Buffer & clear ();

        Buffer & reserve ( size_t cap );
        Buffer & compact ();

        Buffer & operator= ( const Buffer & that );
        Buffer & operator+= ( const Buffer & that );
        bool operator== ( const Buffer & that ) const;

    };

    class BufferBytesView : public Buffer {

        public:

        Buffer & set ( const uint8_t * mem, size_t mem_len );
        Buffer & cat ( const uint8_t * mem, size_t mem_len );
        char cmp ( const uint8_t * mem, size_t mem_len ) const;

    };

    class BufferCharView : public Buffer {

        public:

        Buffer & set ( const char * cstr );
        Buffer & cat ( const char * cstr );
        char cmp ( const char * cstr ) const;

    };

}
}

#endif

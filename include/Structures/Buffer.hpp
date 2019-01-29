#ifndef RILL_STUCTURES_BUFFER
#define RILL_STUCTURES_BUFFER

#include <cstddef>
#include <cstdint>

namespace Rill {
namespace Structures {

    class BufferBytesView;
    class BufferCharView;
    class BufferUTF8View;

    class Buffer {

        protected:

        uint8_t _bytes;
        size_t  _length;
        size_t  _capacity;

        Buffer & _set ( const uint8_t * that, size_t that_len );
        Buffer & _append ( const uint8_t * that, size_t that_len );
        bool _compare ( const uint8_t * that, size_t that_len ) const;

        public:

        Buffer ();
        Buffer ( size_t initial_capacity );
        Buffer ( const Buffer & that );
        Buffer ( const Buffer && that );
        ~Buffer ();

        size_t length () const;
        size_t capacity () const;

        Buffer & reserve ( size_t new_capacity );
        Buffer & compact ();
        Buffer & clear ();

        bool operator== ( const Buffer & that ) const;
        bool operator!= ( const Buffer & that ) const;
        bool operator< ( const Buffer & that ) const;

        operator uint8_t * ();
        operator const uint8_t * () const;

        Buffer & operator= ( const Buffer & that );
        Buffer & operator+= ( const Buffer & that );

        uint8_t & operator[] ( size_t index );
        uint8_t operator[] ( size_t index ) const;

        BufferBytesView & asBytes ();
        BufferCharView & asChars ();
        BufferUTF8View & asUTF8 ();

        const BufferBytesView & asBytes () const;
        const BufferCharView & asChars () const;
        const BufferUTF8View & asUTF8 () const;

    };

    class BufferBytesView : public Buffer {

        public:

        Buffer & set ( const uint8_t * that, size_t that_len );
        Buffer & append ( const uint8_t * that, size_t that_len );
        bool compare ( const uint8_t * that, size_t that_len ) const;

    };

    class BufferCharView : public Buffer {

        public:

        Buffer & operator= ( const char * that );
        Buffer & operator+= ( const char * that );
        bool operator== ( const char * that ) const;

    };

}
}

#endif

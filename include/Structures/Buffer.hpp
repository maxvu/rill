#ifndef RILL_STRUCTURES_BUFFER
#define RILL_STRUCTURES_BUFFER

namespace Rill {
namespace Structures {

    class ByteBuffer;
    class CharBuffer;
    class UTF8Buffer;

    class Buffer {

        protected:

        uint8_t * bytes;
        size_t len;
        size_t cap;

        public:

        static Buffer fromChars ( const char * cstr );
        static Buffer fromBytes ( const uint8_t * bytes );

        Buffer ();
        Buffer ( const Buffer & that );
        Buffer ( const Buffer && that );
        ~Buffer ();

        size_t length () const;
        size_t capacity () const;

        Buffer & reserve ( size_t new_capacity );
        Buffer & compact ();

        Buffer & operator+= ( const Buffer & that );

        bool operator== ( const Buffer & that ) const;
        operator bool () const;

        ByteBuffer & asBytes ();
        CharBuffer & asChars ();
        UTF8Buffer & asUTF8  ();

        const ByteBuffer & asBytes () const;
        const CharBuffer & asChars () const;
        const UTF8Buffer & asUTF8  () const;

    };

    class ByteBuffer : public Buffer {

        ByteBuffer & set ( uint8_t * mem, size_t mem_len );
        ByteBuffer & cat ( uint8_t * mem, size_t mem_len );
        char cmp ( uint8_t * mem, size_t mem_len ) const;
        uint8_t operator[] ( size_t index );
        operator const uint8_t * () const;

    };

    class CharBuffer : public Buffer {


        CharBuffer & operator= ( const char * cstr );
        CharBuffer & operator+= ( const char * cstr );
        char operator[] ( size_t index );
        operator const char * () const;

    };

    class UTF8Buffer : public Buffer {

        class Iter {

            protected:

            const Buffer & buffer;
            size_t position;

            public:

            Iter ( const Buffer & buffer );

            Iter & operator++ (int) const;
            operator bool () const;
            int codepoint () const;

        };

        Iter & begin () const;
        size_t length () const;

    };

}
}

#endif

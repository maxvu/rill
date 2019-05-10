#ifndef RILL_BUFFER
#define RILL_BUFFER

#include <type_traits>

#define RILL_BUFFER_MINIMUM_SIZE 4
#define RILL_BUFFER_DEFAULT_SIZE 16

namespace Rill {

    class BufferCharView;
    class BufferUTF8View;

    class Buffer {

        protected:
        uint8_t * bytes;
        size_t len;
        size_t cap;
        Buffer & resize ( size_t new_capacity );

        public:
        Buffer ();
        Buffer ( size_t initial_capacity );
        Buffer ( uint8_t * mem, size_t mem_length );
        Buffer ( const Buffer & that );
        Buffer ( const Buffer && that );
        ~Buffer ();

        size_t length () const;
        Buffer & reserve ( size_t new_capacity );
        Buffer & compact ();

        Buffer operator+ ( const Buffer & that ) const;
        Buffer & operator+= ( const Buffer & that );
        bool operator== ( const Buffer & that ) const;
        bool operator!= ( const Buffer & that ) const;
        Buffer & operator= ( const Buffer & that );

        Buffer & set ( uint8_t * mem, size_t mem_length );
        Buffer & cat ( uint8_t * mem, size_t mem_length );
        bool eq ( uint8_t * mem, size_t mem_length ) const;

        uint8_t & operator[] ( size_t index );
        uint8_t operator[] ( size_t index ) const;
        operator uint8_t * ();
        operator const uint8_t * () const;
        Buffer & fill ( uint8_t byte );
        Buffer & clear ();

        template <bool isConst>
        class BufferCharView {

            typedef typename
            std::conditional<isConst, const Buffer &, Buffer &> BufferRefT;

            BufferRefT buffer;

            public:
            BufferCharView ( BufferRefT buffer );
            char & operator[] ( size_t index );
            char & operator[] ( size_t index ) const;
            size_t length () const;
            BufferCharView & operator+= ( const char * cstr );
            bool operator== ( const char * cstr );
            bool operator!= ( const char * cstr );
            bool operator> ( const char * cstr );
            bool operator< ( const char * cstr );

        };

        BufferCharView<false> & asChar ();
        BufferCharView<true> & asChar () const;

        class BufferUTF8View {

            public:

            BufferUTF8View ( const Buffer & buffer );
            size_t length () const;

            class Iter {

                protected:
                const Buffer & buffer;
                size_t index;

                public:
                Iter ( BufferUTF8View & view );
                Iter & operator++ (int);
                int codepoint () const;
                operator bool () const;

            };

        };

        const BufferUTF8View & asUTF8 () const;

    };

}

#endif

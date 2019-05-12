#ifndef RILL_BUFFER
#define RILL_BUFFER

#define RILL_BUFFER_MINIMUM_SIZE 4
#define RILL_BUFFER_DEFAULT_SIZE 16

namespace Rill {

    class BufferBytesView;
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
        Buffer ( const Buffer & that );
        Buffer ( const Buffer && that );
        ~Buffer ();

        Buffer & reserve ( size_t new_capacity );
        Buffer & compact ();
        Buffer & clear ();

        BufferBytesView & asBytes ();
        const BufferBytesView & asBytes () const;

        BufferCharView & asChar ();
        const BufferCharView & asChar () const;

        BufferUTF8View & asUTF8 ();
        const BufferUTF8View & asUTF8 () const;

    };

    class BufferBytesView : public Buffer {

        public:

        size_t length () const;

        BufferBytesView & operator= ( BufferBytesView & that );
        BufferBytesView & operator+= ( BufferBytesView & that );
        bool operator== ( BufferBytesView & that ) const;
        bool operator!= ( BufferBytesView & that ) const;

        BufferBytesView & set ( uint8_t * mem, size_t mem_length );
        BufferBytesView & cat ( uint8_t * mem, size_t mem_length );
        bool eq ( uint8_t * mem, size_t mem_length );

    };

    class BufferCharView : public Buffer {

        public:

        size_t length () const;

        BufferCharView & operator= ( const char * that );
        BufferCharView & operator+= ( const char * that );
        bool operator== ( const char * that ) const;
        bool operator!= ( const char * that ) const;

    };

    class BufferUTF8Iter {

        protected:

        const Buffer & buffer;

        public:

        BufferUTF8Iter ( const Buffer & buffer );

        BufferUTF8Iter & operator++ () const;
        operator bool () const;
        int operator* () const;

    };

    class BufferUTF8View : public Buffer {

        public:

        size_t length () const;

        BufferUTF8View & operator= ( const char * that );
        BufferUTF8View & operator+= ( const char * that );
        bool operator== ( const char * that ) const;
        bool operator!= ( const char * that ) const;

        BufferUTF8Iter begin () const;

    };

}

#endif

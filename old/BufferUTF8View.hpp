#ifndef RILL_BUFFERUTF8VIEW
#define RILL_BUFFERUTF8VIEW

namespace Rill {

class BufferUTF8View {

    protected:

    BufferUTF8View ();

    public:

    size_t length () const;

    class Iter {

        protected:
        const BufferUTF8View & buffer;
        size_t index;

        public:
        Iter ( const BufferUTF8View & view );
        Iter & operator++ (int);
        int codepoint () const;
        operator bool () const;

    };

};

}

#endif

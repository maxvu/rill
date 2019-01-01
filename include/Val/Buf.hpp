#ifndef RILL_VAL_BUF
#define RILL_VAL_BUF

#include "Val/Val.hpp"

#include <cstddef>
#include <vector>

namespace Rill {

    typedef class BufCharView BufCharView;
    typedef class BufBytesView BufBytesView;
    typedef class BufUTF8View BufUTF8View;

    class Buf : public Refcounted {

        protected:

        uint8_t * bytes;
        size_t len;
        size_t cap;

        public:

        Buf ();
        Buf ( size_t initial_capacity );
        Buf ( const Buf & other );
        Buf ( const char * cstr );
        ~Buf ();

        operator bool () const;

        Buf & operator= ( const Buf & other );
        Buf & operator+= ( const Buf & other );
        bool operator== ( const Buf & other ) const;
        bool operator!= ( const Buf & other ) const;

        size_t length () const;
        Buf & reserve ( size_t new_capacity );
        Buf & compact ();
        Buf & clear ();

        BufCharView & asChars ();
        BufBytesView & asBytes ();
        BufUTF8View & asUTF8 ();

    };

    class BufCharView : public Buf {

        BufCharView & operator= ( const char * cstr );
        BufCharView & operator+= ( const char * cstr );
        bool operator== ( const char * cstr ) const;
        bool operator!= ( const char * cstr ) const;
        char & operator[] ( size_t index );
        const char & operator[] ( size_t index ) const;

    };

    class BufBytesView : public Buf {

        BufBytesView & set ( uint8_t * mem, size_t mem_len );
        BufBytesView & cat ( uint8_t * mem, size_t mem_len );
        int cmp ( uint8_t * mem, size_t mem_len );
        uint8_t & operator[] ( size_t index );
        const uint8_t & operator[] ( size_t index ) const;

    };

    class BufUTF8Iter {

        protected:

        const Buf & buf;
        size_t pos;

        public:

        BufUTF8Iter ( const Buf & buf );

        BufUTF8Iter & operator++ ();
        unsigned int operator* () const;
        operator bool () const;

    };

    class BufUTF8View : public Buf {

        BufUTF8View & operator+= ( unsigned int codepoint ) ;
        BufUTF8Iter begin () const;

    };

}

#endif

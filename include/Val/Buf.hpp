#ifndef RILL_VAL_BUF
#define RILL_VAL_BUF

#include "Val/Slab.hpp"
#include "Val/Val.hpp"

#include <cstddef>
#include <cstdint>

#define RILL_VALL_BUF_MINSIZE 8
#define RILL_VALL_BUF_DEFAULSIZE 16
#define RILL_VALL_BUF_GROWTHCOEFF 2.0

namespace Rill {

    class Buf : public Val {

        protected:

        Slab<uint8_t> bytes;
        size_t len;

        public:

        Buf ();
        Buf ( size_t initial_capacity );
        Buf ( const Buf & other );
        ~Buf ();

        Val & lease ();
        int release ();
        Val & exclude ();
        Val * clone () const;
        operator bool () const;
        bool containsRef ( const Val * needle );

        size_t length () const;
        size_t capacity () const;

        Buf & reserve ( size_t min_capacity );
        Buf & compact ();

        operator uint8_t & ();
        operator const uint8_t & () const;

        Buf & operator= ( const Buf & other );
        Buf & operator= ( const char * cstr );

        Buf & operator+= ( const Buf & other );
        Buf & operator+= ( const char * cstr );

        bool operator== ( const Buf & other ) const;
        bool operator== ( const char * cstr ) const;

        Buf substr ( size_t start, size_t len ) const;

        Buf & clear ();

    };

}

#endif

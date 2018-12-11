#ifndef RILL_VAL_BUFFER
#define RILL_VAL_BUFFER

#include "Val/Slab.hpp"
#include "Val/Val.hpp"

#include <cstddef>
#include <cstdint>

#define RILL_VALL_BUFFER_MINSIZE
#define RILL_VALL_BUFFER_DEFAULSIZE
#define RILL_VALL_BUFFER_GROWTHCOEFF 2.0

namespace Rill {

    class Buffer : public Val {

        protected:

        Slab<uint8_t> bytes;
        size_t len;

        public:

        Buffer ();
        Buffer ( size_t initial_capacity );
        Buffer ( const Buffer & other );
        ~Buffer ();

        size_t length () const;
        size_t capacity () const;

        Buffer & reserve ( size_t min_capacity );
        Buffer & compact ();

        operator uint8_t & ();
        operator const uint8_t & () const;

        Buffer & operator= ( const Buffer & other );
        Buffer & operator= ( const char * cstr );

        Buffer & operator+= ( const Buffer & other );
        Buffer & operator+= ( const char * cstr );

        bool operator== ( const Buffer & other ) const;
        bool operator== ( const char * cstr ) const;

        Buffer & clear ();

    };

}

#endif

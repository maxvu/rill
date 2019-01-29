#ifndef RILL_STUCTURES_BUFFERUTF8VIEW
#define RILL_STUCTURES_BUFFERUTF8VIEW

#include "Structures/Buffer.hpp"

#include <cstddef>
#include <cstdint>

namespace Rill {
namespace Structures {

    class BufferUTF8Iter {

        protected:

        const Buffer & _buffer;
        size_t         _position;
        size_t         _codepoint;
        uint8_t        _n_bytes;

        public:

        BufferUTF8Iter( const BufferUTF8View & buffer );
        BufferUTF8Iter( const BufferUTF8Iter & that );

        BufferUTF8Iter & operator++ (int);
        operator bool () const;
        size_t decode () const;

        Buffer operator- ( const BufferUTF8Iter & that ) const;
        bool operator== ( const BufferUTF8Iter & that ) const;
        bool operator!= ( const BufferUTF8Iter & that ) const;
        bool operator< ( const BufferUTF8Iter & that ) const;

    };

    class BufferUTF8View : public Buffer {

        public:

        BufferUTF8Iter begin () const;

    };

}
}

#endif

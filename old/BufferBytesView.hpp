#ifndef RILL_BUFFERBYTESVIEW
#define RILL_BUFFERBYTESVIEW

#include "Buffer.hpp"

namespace Rill {

class BufferBytesView : public Buffer {

    protected:

    BufferBytesView ();

    public:

    BufferBytesView & set ( uint8_t * mem, size_t mem_length );
    BufferBytesView & cat ( uint8_t * mem, size_t mem_length );
    bool eq ( uint8_t * mem, size_t mem_length ) const;

    uint8_t & operator[] ( size_t index );
    uint8_t operator[] ( size_t index ) const;
    operator uint8_t * ();
    operator const uint8_t * () const;
    BufferBytesView & fill ( uint8_t byte );

};

}

#endif

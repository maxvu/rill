#ifndef RILL_BUFFERCHARVIEW
#define RILL_BUFFERCHARVIEW

#include "Buffer.hpp"

namespace Rill {

class BufferCharView : public Buffer {

    protected:

    BufferCharView ();

    public:

    char & operator[] ( size_t index );
    char & operator[] ( size_t index ) const;
    size_t length () const;
    BufferCharView & operator+= ( const char * cstr );
    bool operator== ( const char * cstr );
    bool operator!= ( const char * cstr );

};

}

#endif

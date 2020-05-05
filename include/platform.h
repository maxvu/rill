#ifndef RILL_PLATFORM
#define RILL_PLATFORM

namespace rill {

    #ifdef RILL_32BIT
        #define IXX int
        #define UXX unsigned int
        #define FXX float
        const int REF_SIZE = 9;
        const int TAG_SIZE = 20;
    #else
        #define IXX long
        #define UXX unsigned long
        #define FXX double
        const int REF_SIZE = 16;
        const int TAG_SIZE = 27;
    #endif

}

#endif

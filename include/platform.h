#ifndef RILL_PLATFORM
#define RILL_PLATFORM

namespace rill {

    #ifdef RILL_32BIT
        typedef int           IXX;
        typedef unsigned int  UXX;
        typedef float         UXX;
        constexpr UXX RHEAD_REF_SIZE = 8;
        constexpr UXX RHEAD_TAG_SIZE = 21;
    #else
        typedef long          IXX;
        typedef unsigned long UXX;
        typedef double        FXX;
        constexpr UXX RHEAD_REF_SIZE = 8;
        constexpr UXX RHEAD_TAG_SIZE = 53;
    #endif

}

#endif

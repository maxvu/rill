#ifndef RILL_PLATFORM
#define RILL_PLATFORM

#include <stdint.h>

    #ifdef RILL_32BIT
        typedef int32_t  IXX;
        typedef uint32_t UXX;
        typedef float    FXX;
        #define RVAL_TAG_LENGTH 23
        #define RVAL_REF_LENGTH 6
    #else
        typedef int64_t  IXX;
        typedef uint64_t UXX;
        typedef double   FXX;
        #define RVAL_TAG_LENGTH 55
        #define RVAL_REF_LENGTH 6
    #endif

#endif

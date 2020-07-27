#ifndef RILL_PLATFORM
#define RILL_PLATFORM

#ifdef RILL_32BIT
    #define IXX int
    #define UXX unsigned int
    #define FXX float
    #define RVAL_HEADER_TAG_SIZE 21
#else
    #define IXX int
    #define UXX unsigned int
    #define FXX double
    #define RVAL_HEADER_TAG_SIZE 53
#endif

#endif

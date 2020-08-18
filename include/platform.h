#ifndef RILL_PLATFORM
#define RILL_PLATFORM

#ifdef RILL_32BIT
    #define IXX int
    #define UXX unsigned int
    #define FXX float
    #define RVAL_HEADER_TAG_SIZE 21
    #define RVAL_HEADER_REF_SIZE 8
#else
    #define IXX long
    #define UXX unsigned long
    #define FXX double
    #define RVAL_HEADER_TAG_SIZE 53
    #define RVAL_HEADER_REF_SIZE 8
#endif

#endif

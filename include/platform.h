#ifndef RILL_PLATFORM
#define RILL_PLATFORM

    #ifdef RILL32_BIT
        #define IXX int
        #define UXX unsigned int
        #define FXX float
        #define RVAL_TAG_SIZE 20
        #define RVAL_REF_SIZE 9
    #else
        #define IXX long
        #define UXX unsigned long
        #define FXX double
        #define RVAL_TAG_SIZE 27
        #define RVAL_REF_SIZE 16
    #endif

#endif

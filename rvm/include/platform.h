#ifndef RILL_PLATFORM
#define RILL_PLATFORM

#ifdef RILL_32BIT
    #define IXX int
    #define UXX unsigned int
    #define FXX float
#else
    #define IXX long
    #define UXX unsigned long
    #define FXX double
#endif

#endif

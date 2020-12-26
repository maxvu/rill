#ifndef RILL_ENV
#define RILL_ENV

#if _WIN32 || _WIN64
    #if _WIN32
        #define RILL_32BIT
    #endif
#endif

#if __GNUC__
    #if __x86_64__ || __ppc64__
    #else
        #define RILL_32BIT
    #endif
#endif

#endif

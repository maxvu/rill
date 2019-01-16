#ifndef RILL_CONFIG
#define RILL_CONFIG

    #define RILL_IXX_TYPE int64_t
    #define RILL_UXX_TYPE uint64_t
    #define RILL_FXX_TYPE double

    #define RILL_ALLOC(N)          malloc( N )
    #define RILL_DEALLOC(X)        free( X )

    #ifndef RILL_DISABLE_CONSOLE_COLOR
        #define RILL_CONSOLE_RED "\033[1;31m"
        #define RILL_CONSOLE_GREEN "\033[1;32m"
        #define RILL_CONSOLE_CLEAR "\033[0m"
    #else
        #define RILL_CONSOLE_RED   ""
        #define RILL_CONSOLE_GREEN ""
        #define RILL_CONSOLE_CLEAR ""
    #endif

#endif

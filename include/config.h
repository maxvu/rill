#ifndef RILL_CONFIG
#define RILL_CONFIG

    #define RILL_IXX_TYPE int64_t
    #define RILL_UXX_TYPE uint64_t
    #define RILL_FXX_TYPE double

    #define RILL_ALLOC(N)          malloc( N )
    #define RILL_DEALLOC(X)        free( X )

#endif

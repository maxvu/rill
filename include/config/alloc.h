#ifndef RILL_CONFIG_ALLOC
#define RILL_CONFIG_ALLOC

    #include <stdlib.h>

    #define RILL_ALLOC(N)          malloc( N )
    #define RILL_DEALLOC(X)        free( X )

#endif

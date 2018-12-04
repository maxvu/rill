#ifndef RILL_ENVIRONMENT
#define RILL_ENVIRONMENT

    // Turn off all debugging features.
    #ifdef RVAL_RELEASE
        #undef RVAL_TATTLE
        #undef RVAL_TRACE_ALLOC
    #else

    #endif

    // Intercept allocation calls.
    #ifdef RVAL_TRACE_ALLOC
        #define RILL_ALLOC(n) malloc(n)
        #define RILL_DEALLOC(x) free(x)
        #define RILL_REALLOC(x, n) realloc(x, n)
    #else
        #define RILL_ALLOC(n) malloc(n)
        #define RILL_DEALLOC(x) free(x)
        #define RILL_REALLOC(x, n) realloc(x, n)
    #endif

    // Special byte-shuffling for 32-bit systems.
    #ifdef RILL_32BIT
        #error "32-bit compilation not yet supported."
    #endif

    #define RILL_CONSOLE_GREEN "\033[1;32m"
    #define RILL_CONSOLE_RED "\033[1;31m"
    #define RILL_CONSOLE_RESET "\033[0m"

    // Disable console coloring.
    #ifndef RILL_DISABLE_CONSOLE_COLOR
        #define RILL_CONSOLE_SUCCESS( MSG ) RILL_CONSOLE_GREEN #MSG RILL_CONSOLE_RESET
        #define RILL_CONSOLE_FAILURE( MSG ) RILL_CONSOLE_RED #MSG RILL_CONSOLE_RESET
    #else
        #define RILL_CONSOLE_FAILURE( MSG ) #MSG
        #define RILL_CONSOLE_SUCCESS( MSG ) #MSG
    #endif

    // Programatically trigger breakpoints in debugging.
    #ifdef RVAL_TATTLE
        #include <signal.h>
        #include <stdio.h>
        #define TATTLE { printf( "~tattling~\n" ); raise(SIGINT); }
    #else
        #define TATTLE
    #endif

#endif

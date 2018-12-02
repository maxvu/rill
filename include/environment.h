#ifndef RILL_ENVIRONMENT
#define RILL_ENVIRONMENT

    // Turn off all debugging features.
    #ifdef RVAL_RELEASE
        #undef RVAL_TATTLE
    #else
        #define RVAL_TATTLE
    #endif

    // Intercept allocation calls.
    #ifdef RVAL_TRACE_ALLOC

    #else
        #define RILL_ALLOC(n) malloc(n)
        #define RILL_DEALLOC(x) free(x)
    #endif

    // Special byte-shuffling for 32-bit systems.
    #ifdef RILL_32BIT
        #error "32-bit compilation not yet supported."
    #endif

    // Disable console coloring.
    #ifndef RILL_DISABLE_CONSOLE_COLOR
        #define RILL_CONSOLE_GREEN( msg ) "\033[1;32m" "msg" "\033[0m"
        #define RILL_CONSOLE_RED( msg ) "\033[1;31m" "msg" "\033[0m"
    #else
        #define RILL_CONSOLE_GREEN( msg ) "msg"
        #define RILL_CONSOLE_RED( msg ) "msg"
    #endif

    // Programatically trigger breakpoints in debugging.
    #ifdef RVAL_TATTLE
        #include <signal.h>
        #define TATTLE(EXPR) if ( !(EXPR) ) { raise(SIGINT); }
    #else
        #define TATTLE(EXPR)
    #endif

#endif

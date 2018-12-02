#ifndef RILL_ENVIRONMENT
#define RILL_ENVIRONMENT

    #ifdef RILL_32BIT
        #error "32-bit compilation not yet supported."
    #endif

    #ifdef RILL_DISABLE_CONSOLE_COLOR
        #define RILL_CONSOLE_GREEN( msg ) "\033[1;32m" msg "\033[0m"
        #define RILL_CONSOLE_RED( msg ) "\033[1;31m" msg "\033[0m"
    #else
        #define RILL_CONSOLE_GREEN( msg ) msg
        #define RILL_CONSOLE_RED( msg ) msg
    #endif

#endif

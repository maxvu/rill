#ifndef RILL_CONFIG_COLOR
#define RILL_CONFIG_COLOR

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

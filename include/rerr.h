#ifndef RILL_RERR
#define RILL_RERR

#include "platform.h"

typedef UXX rerr;

enum {
    RERR_OK  = 0,
    RERR_ARG = 1,
    RERR_USE = 2,
    RERR_MEM = 3
};

const char * rerr_describe ();

#endif

#ifndef RILL_RERR
#define RILL_RERR

#include "platform.h"

typedef enum rerr : char {
    RERR_OK       = 0,
    RERR_MEM      = 16,
    RERR_ARG_NULL = 64,
    RERR_ARG_TYPE = 65,
    RERR_ARG_OVRF = 66
} rerr;

char rerr_ok              ( rerr err );
const char * rerr_explain ( rerr err );

#endif

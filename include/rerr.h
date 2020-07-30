#ifndef RILL_RERR
#define RILL_RERR

#include "platform.h"

typedef enum rerr : char {
    RERR_OK       = 0,
    RERR_SYS_MEM  = 16,
    RERR_SYS_OVRF = 17,
    RERR_ARG_NULL = 64,
    RERR_ARG_TYPE = 65
} rerr;

char rerr_ok              ( rerr err );
const char * rerr_explain ( rerr err );

#endif

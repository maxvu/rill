#ifndef RILL_RERR
#define RILL_RERR

#include "platform.h"

typedef enum rerr : UXX {
    RERR_OK       = 0,
    RERR_MEM  = 16,
    RERR_OVRF = 17,
    RERR_NULL = 64,
    RERR_TYPE = 65
} rerr;

char rerr_ok              ( rerr err );
const char * rerr_explain ( rerr err );

#endif

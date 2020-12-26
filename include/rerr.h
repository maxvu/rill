#ifndef RILL_RERR
#define RILL_RERR

#include "platform.h"

typedef enum rerr : char {
    RERR_OK       = 0,  // no error
    RERR_MEM      = 16, // memory allocation failure
    RERR_ARG_NULL = 64, // unexpected null argument
    RERR_ARG_TYPE = 65, // argument of unexpected type
    RERR_ARG_OVRF = 66  // overflow
} rerr;

char rerr_ok              ( rerr err );
const char * rerr_explain ( rerr err );

#endif

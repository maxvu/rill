#ifndef RILL_RVAL_RUXX
#define RILL_RVAL_RUXX

#include "config/arch.h"

typedef struct rval rval;

rval ruxx ( RILL_UXX_TYPE u );
void ruxx_set ( rval * val, RILL_UXX_TYPE u );
RILL_UXX_TYPE ruxx_get ( rval * val );

#endif

#ifndef RILL_RVAL_RUXX
#define RILL_RVAL_RUXX

#include "config/arch.h"

typedef struct RVal RVal;

RVal ruxx ( RILL_UXX_TYPE u );
void ruxx_set ( RVal * val, RILL_UXX_TYPE u );
RILL_UXX_TYPE ruxx_get ( RVal * val );

#endif

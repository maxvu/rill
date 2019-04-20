#ifndef RILL_RVAL_RIXX
#define RILL_RVAL_RIXX

#include "config/arch.h"

typedef struct RVal RVal;

RVal rixx ( RILL_IXX_TYPE i );
void rixx_set ( RVal * val, RILL_IXX_TYPE i );
RILL_IXX_TYPE rixx_get ( RVal * val );

#endif

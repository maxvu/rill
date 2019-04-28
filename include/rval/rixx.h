#ifndef RILL_RVAL_RIXX
#define RILL_RVAL_RIXX

#include "config/arch.h"

typedef struct rval rval;

rval rixx ( RILL_IXX_TYPE i );
void rixx_set ( rval * val, RILL_IXX_TYPE i );
RILL_IXX_TYPE rixx_get ( rval * val );

#endif

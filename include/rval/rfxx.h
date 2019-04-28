#ifndef RILL_RVAL_RFXX
#define RILL_RVAL_RFXX

#include "config/arch.h"

typedef struct rval rval;

rval rfxx ( RILL_FXX_TYPE f );
void rfxx_set ( rval * val, RILL_FXX_TYPE f );
RILL_FXX_TYPE rfxx_get ( rval * val );
int rfxx_isfinite ( rval * val );
int rfxx_isinf ( rval * val );
int rfxx_isnan ( rval * val );

#endif

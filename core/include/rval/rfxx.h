#ifndef RILL_RVAL_RFXX
#define RILL_RVAL_RFXX

#include "config/arch.h"

typedef struct RVal RVal;

RVal rfxx ( RILL_FXX_TYPE f );
void rfxx_set ( RVal * val, RILL_FXX_TYPE f );
RILL_FXX_TYPE rfxx_get ( RVal * val );
int rfxx_isfinite ( RVal * val );
int rfxx_isinf ( RVal * val );
int rfxx_isnan ( RVal * val );

#endif

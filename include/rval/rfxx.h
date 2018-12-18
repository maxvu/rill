#ifndef RILL_RVAL_RFXX
#define RILL_RVAL_RFXX

#include "rval/rval.h"

RVal rfxx ( RILL_FXX_TYPE );
RILL_FXX_TYPE rfxx_get ( RVal * val );
void rfxx_set rfxx_set ( RVal * val, RILL_FXX_TYPE f );

#endif

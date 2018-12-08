#ifndef RILL_RVAL_PRIMITIVES
#define RILL_RVAL_PRIMITIVES

#include "rval/rval.h"

void uxx_set ( RVal * val, RILL_UXX_TYPE u );
RILL_UXX_TYPE uxx_get ( RVal * val );

void ixx_set ( RVal * val, RILL_IXX_TYPE i );
RILL_IXX_TYPE ixx_get ( RVal * val );

void fxx_set ( RVal * val, RILL_FXX_TYPE f );
RILL_FXX_TYPE fxx_get ( RVal * val );

#endif

#ifndef RILL_RVAL_NUMERIC
#define RILL_RVAL_NUMERIC

#include "environment.h"

#include "rval/rref.h"

RILL_UXX_TYPE __ruxx_get ( RRef * ref );
void __ruxx_set ( RRef * ref, RILL_UXX_TYPE u );

RILL_IXX_TYPE __rixx_get ( RRef * ref );
void __rixx_set ( RRef * ref, RILL_IXX_TYPE i );

RILL_FXX_TYPE __rfxx_get ( RRef * ref );
void __rfxx_set ( RRef * ref, RILL_FXX_TYPE f );

#endif

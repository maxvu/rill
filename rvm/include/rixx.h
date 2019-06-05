#ifndef RVM_RIXX
#define RVM_RIXX

#include "rval.h"

typedef unsigned int rerr;

rval rixxq ();
rval rixxqv ( int i );
rerr rixx_set ( rval * val, int i );
int rixx_get ( rval * val );

#endif

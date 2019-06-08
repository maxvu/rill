#ifndef RVM_RUXX
#define RVM_RUXX

typedef unsigned int rerr;

#include "rval.h"

rval ruxxq ( unsigned int i );
rerr ruxx_set ( rval * val, unsigned int u );
unsigned int ruxx_get ( rval * val );

#endif

#ifndef RVM_RFXX
#define RVM_RFXX

#include "rval.h"

typedef unsigned int rerr;

rerr rfxx_set ( rval * val, double i );
double rfxx_get ( rval * val );

#endif

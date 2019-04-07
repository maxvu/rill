#ifndef RILL_RLEX
#define RILL_RLEX

#include "rval/rval.h"

/*
    places an rvec of rlextok's into `dst`
*/

int rlex ( RVal * dst, RVal * lexbuf );

#endif

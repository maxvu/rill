#ifndef RILL_RLEX
#define RILL_RLEX

#include "rval/rval.h"

#define RILL_LEX_RESULT_BUFFER_SIZE 128

/*
    places an rvec of rlextok's into `dst`
*/

int rlex ( RVal * dst, RVal * lexbuf );

#endif

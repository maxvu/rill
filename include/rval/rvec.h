#ifndef RILL_RVAL_RVEC
#define RILL_RVAL_RVEC

#include "rval/rval.h"

#include <stddef.h>

#define RILL_RVEC_MINCAP 8
#define RILL_RVEC_DEFAULTCAP 16
#define RILL_RVEC_GROWTHFACT 2.25


typedef struct rvec {
    size_t  ref;
    size_t  len;
    size_t  cap;
    RVal    vals[];
} RVec;

RVal rvec ( size_t init_cap );
int rvec_reserve ( RVal * vec, size_t new_cap );
int rvec_compact ( RVal * vec );
size_t rvec_len ( RVal * vec );
RVal * rvec_get ( RVal * vec, size_t index );
int rvec_set ( RVal * vec, size_t index, RVal * item );
int rvec_push ( RVal * vec, RVal * item );
size_t rvec_pop ( RVal * vec );
void rvec_clear ( RVal * vec );

#endif

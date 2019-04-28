#ifndef RILL_RVAL_RVEC
#define RILL_RVAL_RVEC

#include "rval/rval.h"

#define RILL_RVEC_MINSIZ 4
#define RILL_RVEC_DEFSIZ 12
#define RILL_RVEC_GROWTH 2.0

typedef struct RVec {
    size_t len;
    size_t cap;
    size_t ref;
    rval   vls[];
} RVec;

rval rvec ();
int rvec_init ( rval * val, size_t cap );
size_t rvec_len ( rval * vec );
int rvec_reserve ( rval * vec, size_t cap );
int rvec_compact ( rval * vec );
int rvec_clone ( rval * dst, rval * src );
int rvec_exclude ( rval * vec );
int rvec_release ( rval * vec );
int rvec_push ( rval * vec, rval * item );
int rvec_pop ( rval * vec );
rval * rvec_get ( rval * vec, size_t idx );
int rvec_set ( rval * vec, size_t idx, rval * item );
int rvec_fill ( rval * vec, rval * item, size_t n );
int rvec_reverse ( rval * vec );
int rvec_concat ( rval * dst, rval * src );
int rvec_clear ( rval * vec );

#endif

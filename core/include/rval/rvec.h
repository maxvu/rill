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
    RVal   vls[];
} RVec;

RVal rvec ();
int rvec_init ( RVal * val, size_t cap );
size_t rvec_len ( RVal * vec );
int rvec_reserve ( RVal * vec, size_t cap );
int rvec_compact ( RVal * vec );
int rvec_clone ( RVal * dst, RVal * src );
int rvec_exclude ( RVal * vec );
int rvec_release ( RVal * vec );
int rvec_push ( RVal * vec, RVal * item );
int rvec_pop ( RVal * vec );
RVal * rvec_get ( RVal * vec, size_t idx );
int rvec_set ( RVal * vec, size_t idx, RVal * item );
int rvec_fill ( RVal * vec, RVal * item, size_t n );
int rvec_reverse ( RVal * vec );
int rvec_concat ( RVal * dst, RVal * src );
int rvec_clear ( RVal * vec );

#endif

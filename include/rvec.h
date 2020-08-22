#ifndef RILL_RVEC
#define RILL_RVEC

#include "platform.h"
#include "rerr.h"

typedef struct rval rval;

rval * rvec_create  ( UXX    cap, rerr * err );
UXX    rvec_len     ( rval * vec, rerr * err );
void   rvec_reserve ( rval * vec, UXX    cap, rerr * err );
void   rvec_compact ( rval * vec, rerr * err );
void   rvec_push    ( rval * vec, rval * itm, rerr * err );
rval * rvec_front   ( rval * vec, rerr * err );
rval * rvec_back    ( rval * vec, rerr * err );
void   rvec_pop     ( rval * vec, rerr * err );
void   rvec_get     ( rval * vec, UXX    idx, rerr * err );
void   rvec_set     ( rval * vec, UXX    idx, rval * itm, rerr * err );
void   rvec_reverse ( rval * vec, rerr * err );
void   rvec_clear   ( rval * vec, rerr * err );

#endif

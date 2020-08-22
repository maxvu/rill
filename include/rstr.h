#ifndef RILL_RSTR
#define RILL_RSTR

#include "platform.h"
#include "rerr.h"

typedef struct rval rval;
typedef struct rstr rstr;

rval * rstr_create  ( UXX    cap, rerr * err );
UXX    rstr_len     ( rval * str, rerr * err );
rval * rstr_reserve ( rval * str, UXX    cap, rerr * err );
rval * rstr_compact ( rval * str, rerr * err );
rval * rstr_cpy     ( rval * dst, rval * src, rerr * err );
rval * rstr_cat     ( rval * dst, rval * src, rerr * err );
int    rstr_cmp     ( rval * a,   rval * b,   rerr * err );
rval * rstr_cpyc    ( rval * str, const char * src, rerr * err );
rval * rstr_catc    ( rval * str, const char * src, rerr * err );
int    rstr_cmpc    ( rval * a,   const char * b,   rerr * err );
rval * rstr_clear   ( rval * str, rerr * err );

#endif

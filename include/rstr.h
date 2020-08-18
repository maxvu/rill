#ifndef RILL_RSTR
#define RILL_RSTR

#include "platform.h"
#include "rerr.h"

typedef struct rval rval;

rval * rstr_create  ( UXX    cap, rerr * err );
UXX    rstr_len     ( rval * str, rerr * err );
void   rstr_reserve ( rval * str, UXX    cap, rerr * err );
void   rstr_compact ( rval * str, rerr * err );
void   rstr_cpy     ( rval * dst, rval * src, rerr * err );
void   rstr_cat     ( rval * dst, rval * src, rerr * err );
int    rstr_cmp     ( rval * a,   rval * b,   rerr * err );
void   rstr_cpyc    ( rval * str, char * src, rerr * err );
void   rstr_catc    ( rval * str, char * src, rerr * err );
void   rstr_repeat  ( rval * str, UXX    n,   rerr * err );
void   rstr_clear   ( rval * str, rerr * err );
void   rstr_destroy ( rval * str, rerr * err );

#endif

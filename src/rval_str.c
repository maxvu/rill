#include "rval.h"
#include "rval_impl.h"

void rstr_create  ( UXX     cap, rval ** out, rerr * err );
void rstr_len     ( rval *  str, UXX  *  out, rerr * err );
void rstr_reserve ( rval ** str, UXX     cap, rerr * err );
void rstr_compact ( rval ** str, rerr *  err );
void rstr_cpy     ( rval ** dst, rval *  src, rerr * err );
void rstr_cat     ( rval ** dst, rval *  src, rerr * err );
void rstr_cmp     ( rval *  a,   rval *  b,   rerr * err );
void rstr_cpyc    ( rval ** str, char *  src, rerr * err );
void rstr_catc    ( rval ** str, char *  src, rerr * err );
void rstr_cmpc    ( rval *  str, char *  src, rerr * err );
void rstr_repeat  ( rval ** str, UXX     n,   rerr * err );
void rstr_clear   ( rval *  str, rerr *  err );
void rstr_destroy ( rval ** str, rerr *  err );

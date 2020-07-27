#include "rval.h"
#include "rval_impl.h"

void rvec_create  ( rval ** vec, UXX     cap, rerr * err );
void rvec_len     ( rval *  vec, UXX  *  out, rerr * err );
void rvec_reserve ( rval ** vec, UXX     cap, rerr * err );
void rvec_compact ( rval ** vec, rerr *  err );
void rvec_push    ( rval ** vec, rval *  itm, rerr * err );
void rvec_pop     ( rval *  vec, rval ** out, rerr * err );
void rvec_get     ( rval *  vec, UXX     idx, rval ** itm, rerr * err );
void rvec_set     ( rval *  vec, UXX     idx, rval *  itm, rerr * err );
void rvec_shift   ( rval *  vec, rval ** itm, rerr * err );
void rvec_unshift ( rval ** vec, rval *  itm, rerr * err );
void rvec_reverse ( rval ** vec, rerr *  err );
void rvec_clear   ( rval *  vec, rerr *  err );
void rvec_destroy ( rval ** vec, rerr *  err );

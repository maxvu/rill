#ifndef RILL_RVAL
#define RILL_RVAL

#include "platform.h"
#include "rerr.h"

typedef struct rval rval;

void rval_type     ( rval *  val, char *  typ, rerr * err );
void rval_copy     ( rval ** dst, rval *  src, rerr * err );
void rval_clone    ( rval ** out, rval *  src, rerr * err );
void rval_move     ( rval ** dst, rval ** src, rerr * err );
void rval_contains ( rval *  ndl, rval *  hay, rerr * err );
void rval_ref      ( rval ** val, rerr *  err );
void rval_deref    ( rval ** val, rerr *  err );

void rixx_get  ( rval * num, IXX * out, rerr * err );
void rixx_set  ( rval * num, IXX   i,   rerr * err );
void ruxx_get  ( rval * num, UXX * out, rerr * err );
void ruxx_set  ( rval * num, UXX   u,   rerr * err );
void rfxx_get  ( rval * num, FXX * out, rerr * err );
void rfxx_set  ( rval * num, FXX   f,   rerr * err );

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

void rmap_create  ( rval ** map, UXX    cap, rerr * err );
void rmap_size    ( rval ** map, UXX  * siz, rerr * err );
void rmap_reserve ( rval ** map, UXX    cap, rerr * err );
void rmap_compact ( rval ** map, rerr * err );
void rmap_get     ( rval *  map, rval * key, rval ** out, rerr * err );
void rmap_set     ( rval ** map, rval * key, rval *  val, rerr * err );
void rmap_pop     ( rval *  map, rval * key, rval *  val, rerr * err );
void rmap_keys    ( rval ** map, rval * kys, rerr *  err );
void rmap_vals    ( rval ** map, rval * vls, rerr *  err );
void rmap_merge   ( rval ** dst, rval * src, rerr *  err );
void rmap_clear   ( rval *  map, rerr * err );
void rmap_destroy ( rval ** map, rerr * err );

typedef struct rmap_it rmap_it;

void rmap_begin   ( rval * map, rmap_it * it, rerr * err );
void rmapit_next  ( rmap_it * it, rerr * err );
void rmapit_ok    ( rmap_it * it, rerr * err );
void rmapit_key   ( rmap_it * it, rval ** key, rerr * err );
void rmapit_val   ( rmap_it * it, rval ** val, rerr * err );
void rmapit_del   ( rmap_it * it, rerr * err );
void rmapit_set   ( rmap_it * it, rval * val,  rerr * err );

#endif

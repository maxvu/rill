#ifndef RILL_RVAL
#define RILL_RVAL

#include "platform.h"
#include "rerr.h"

enum rval_types : UXX {
    RVT_IXX = 0,
    RVT_UXX = 1,
    RVT_FXX = 2,
    RVT_STR = 3,
    RVT_VEC = 4,
    RVT_MAP = 5,
    RVT_EXT = 6
};

typedef struct rval rval;

rerr rval_type     ( rval *  val, UXX  *  typ );
rerr rval_copy     ( rval ** dst, rval *  src );
rerr rval_clone    ( rval ** out, rval *  src );
rerr rval_move     ( rval ** dst, rval ** src );
rerr rval_contains ( rval *  ndl, rval *  hay );
rerr rval_ref      ( rval ** val );
rerr rval_deref    ( rval ** val );

rerr rnum_create  ( rval ** out );
rerr rnum_geti    ( rval * num, IXX * out );
rerr rnum_seti    ( rval * num, IXX   i );
rerr rnum_getu    ( rval * num, UXX * out );
rerr rnum_setu    ( rval * num, UXX   u );
rerr rnum_getf    ( rval * num, FXX * out );
rerr rnum_setf    ( rval * num, FXX   f );

rerr rstr_create  ( UXX     cap, rval ** out );
rerr rstr_len     ( rval *  str, UXX  *  out );
rerr rstr_reserve ( rval ** str, UXX     cap );
rerr rstr_compact ( rval ** str );
rerr rstr_cpy     ( rval ** dst, rval *  src );
rerr rstr_cat     ( rval ** dst, rval *  src );
rerr rstr_cmp     ( rval *  a,   rval *  b );
rerr rstr_cpyc    ( rval ** str, char *  src );
rerr rstr_catc    ( rval ** str, char *  src );
rerr rstr_cmpc    ( rval *  str, char *  src );
rerr rstr_repeat  ( rval ** str, UXX     n   );
rerr rstr_clear   ( rval *  str );
rerr rstr_destroy ( rval ** str );

rerr rvec_create  ( rval ** vec, UXX     cap );
rerr rvec_len     ( rval *  vec, UXX  *  out );
rerr rvec_reserve ( rval ** vec, UXX     cap );
rerr rvec_compact ( rval ** vec  );
rerr rvec_push    ( rval ** vec, rval *  itm );
rerr rvec_pop     ( rval *  vec, rval ** out );
rerr rvec_get     ( rval *  vec, UXX     idx, rval ** itm );
rerr rvec_set     ( rval *  vec, UXX     idx, rval *  itm );
rerr rvec_shift   ( rval *  vec, rval ** itm );
rerr rvec_unshift ( rval ** vec, rval *  itm );
rerr rvec_reverse ( rval ** vec  );
rerr rvec_clear   ( rval *  vec  );
rerr rvec_destroy ( rval ** vec  );

rerr rmap_create  ( rval ** map, UXX    cap );
rerr rmap_size    ( rval ** map, UXX  * siz );
rerr rmap_reserve ( rval ** map, UXX    cap );
rerr rmap_compact ( rval ** map );
rerr rmap_get     ( rval *  map, rval * key, rval ** out );
rerr rmap_set     ( rval ** map, rval * key, rval *  val );
rerr rmap_pop     ( rval *  map, rval * key, rval *  val );
rerr rmap_keys    ( rval ** map, rval * kys );
rerr rmap_vals    ( rval ** map, rval * vls );
rerr rmap_merge   ( rval ** dst, rval * src );
rerr rmap_clear   ( rval *  map );
rerr rmap_destroy ( rval ** map );

typedef struct rmap_it rmap_it;

rerr rmap_begin   ( rval * map, rmap_it * it );
rerr rmapit_next  ( rmap_it * it );
rerr rmapit_ok    ( rmap_it * it );
rerr rmapit_key   ( rmap_it * it, rval ** key );
rerr rmapit_val   ( rmap_it * it, rval ** val );
rerr rmapit_del   ( rmap_it * it );
rerr rmapit_set   ( rmap_it * it, rval * val );

#endif

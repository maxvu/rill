#ifndef RILL_RVAL
#define RILL_RVAL

#include "env.h"
#include "rerr.h"

typedef enum rval_type {
    NIL = 0,
    IXX = 1,
    UXX = 2,
    FXX = 3,
    BUF = 4,
    VEC = 5,
    MAP = 6,
    UDO = 7
} rval_type;

typedef struct rval {
    rval_header hed;
} rval;

rerr rval_head_type ( rval ** val );
rerr rval_head_tag ( rval ** val );
rerr rval_head_ref ( rval ** val );

rerr rval_ref    ( rval ** val );
rerr rval_deref  ( rval ** val );
rerr rval_cycles ( rval ** ndl, rval ** hay );
rerr rval_clone  ( rval ** dst, rval ** src );
rerr rval_copy   ( rval ** dst, rval ** src );
rerr rval_compact ( rval ** dst );

rerr rnum_geti ( rval ** num, IXX * i );
rerr rnum_getu ( rval ** num, UXX * u );
rerr rnum_getf ( rval ** num, FXX * f );

rerr rnum_seti ( rval ** num, IXX i );
rerr rnum_setf ( rval ** num, UXX u );
rerr rnum_setu ( rval ** num, FXX f );

rerr rbuf_create ( rval ** buf, size_t siz );
rerr rbuf_reserve ( rval ** buf, size_t siz );
rerr rbuf_len ( rval ** dst, size_t * len );
rerr rbuf_set ( rval ** str, char * cstr );
rerr rbuf_cat ( rval ** dst, rval ** src );
rerr rbuf_get ( rval ** dst, uint8_t ** buf );
rerr rbuf_clear ( rval ** dst );

rerr rvec_create ( rval ** vec, size_t siz );
rerr rvec_reserve ( rval ** vec, size_t siz );
rerr rvec_len ( rval ** vec, size_t * len );
rerr rvec_head ( rval ** vec, rval ** hed );
rerr rvec_tail ( rval ** vec, rval ** tal );
rerr rvec_get ( rval ** vec, size_t idx, rval ** itm );
rerr rvec_set ( rval ** vec, size_t idx, rval ** itm );
rerr rvec_push ( rval ** vec, rval ** itm );
rerr rvec_pop ( rval ** vec );
rerr rvec_clear ( rval ** vec );

rerr rmap_create ( rval ** map, size_t siz );
rerr rmap_reserve ( rval ** map, size_t siz );
rerr rmap_size ( rval ** map, size_t * siz );
rerr rmap_has ( rval ** map, rval ** key );
rerr rmap_get ( rval ** map, rval ** key, rval ** itm );
rerr rmap_set ( rval ** map, rval ** key, rval ** itm );
rerr rmap_unset ( rval ** map, rval ** key );
rerr rmap_keys ( rval ** map, rval ** key_vec );
rerr rmap_vals ( rval ** map, rval ** key_vec );

typedef struct rmap_it rmap_it;

rerr rmap_begin ( rmap ** map, rmap_it * it );
rerr rmapit_ok  ( rmap_it * it, int * ok );
rerr rmapit_key ( rmap_it * it, rval ** key );
rerr rmapit_val ( rmap_it * it, rval ** val );
rerr rmapit_set ( rmap_it * it, rval ** itm );
rerr rmapit_unset ( rmap_it * it );

#endif

#include "rval.h"
#include "rval_impl.h"

typedef struct rmap_slot {
    rval * key;
    rval * val;
} rmap_slot;

typedef struct rmap_it {
    rmap_slot * pos;
    rmap_slot * end;
} rmap_it;

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
void rmap_begin   ( rval * map, rmap_it * it, rerr * err );

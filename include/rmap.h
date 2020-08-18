#ifndef RILL_RVAL
#define RILL_RVAL

#include "platform.h"
#include "rerr.h"

typedef struct rval rval;

void   rmap_create  ( rval * map, UXX     cap, rerr * err );
UXX    rmap_size    ( rval * map, rerr *  err );
void   rmap_reserve ( rval * map, UXX     cap, rerr * err );
void   rmap_compact ( rval * map, rerr *  err );
int    rmap_has     ( rval   map, rval *  key, rerr * err );
rval * rmap_get     ( rval   map, rval *  key, rerr * err );
void   rmap_set     ( rval * map, rval *  key, rval *  val, rerr * err );
void   rmap_pop     ( rval   map, rval *  key, rerr * err );
void   rmap_keys    ( rval * map, rval ** kys, rerr * err );
void   rmap_vals    ( rval * map, rval ** vls, rerr * err );
void   rmap_merge   ( rval * dst, rval *  src, rerr * err );
void   rmap_clear   ( rval * map, rerr *  err );
void   rmap_destroy ( rval * map, rerr *  err );

typedef struct rmap_it rmap_it;

void   rmap_begin  ( rval *    map, rmap_it * it, rerr * err );
int    rmapit_next ( rmap_it * it,  rerr * err,   rerr * err );
int    rmapit_ok   ( rmap_it * it,  rerr * err );
rval * rmapit_key  ( rmap_it * it,  rerr * err );
rval * rmapit_val  ( rmap_it * it,  rerr * err );
void   rmapit_del  ( rmap_it * it,  rerr * err );
rerr   rmapit_set  ( rmap_it * it,  rval * val,   rerr * err );

#endif

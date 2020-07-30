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

rerr rmap_begin   ( rval * map, rmap_it * it );
rerr rmapit_next  ( rmap_it * it );
rerr rmapit_ok    ( rmap_it * it );
rerr rmapit_key   ( rmap_it * it, rval ** key );
rerr rmapit_val   ( rmap_it * it, rval ** val );
rerr rmapit_del   ( rmap_it * it );
rerr rmapit_set   ( rmap_it * it, rval * val );

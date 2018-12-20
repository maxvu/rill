#ifndef RILL_RVAL_RMAP
#define RILL_RVAL_RMAP

#include "rval/rval.h"

#include <stddef.h>

#define RILL_RMAP_MINCAP     8
#define RILL_RMAP_DEFAULTCAP 12
#define RILL_RMAP_GROWTHFACT 2.25
#define RILL_RMAP_MAXLOAD    0.50

typedef struct rmap_slot {
    RVal key;
    RVal val;
} RMapSlot;

typedef struct rmap {
    size_t  ref;
    size_t  occ;
    size_t  cap;
    RMapSlot slots[];
} RMap;

size_t rmap_hash_a ( RVal * key );
size_t rmap_hash_b ( RVal * key );
size_t rmap_hash_c ( RVal * key );
size_t rmap_hash_d ( RVal * key );

RVal rmap ( size_t init_cap );
size_t rmap_size ( RVal * map );
size_t rmap_load ( RVal * map );
int rmap_reserve ( RVal * map, size_t new_cap );
int rmap_compact ( RVal * map );
RVal * rmap_get ( RVal * map, RVal * key );
int rmap_set ( RVal * map, RVal * key, RVal * val );
int rmap_unset ( RVal * map, RVal * key );
int rmap_merge ( RVal * dst, RVal * src );
int rmap_intersect ( RVal * dst, RVal * src );
void rmap_clear ( RVal * map );
int rmap_keys ( RVal * dst_vec, RVal * src_map );
int rmap_vals ( RVal * dst_vec, RVal * src_map );

typedef RMapSlot * RMapIter;

RMapIter rmap_begin ( RVal * map );
RMapIter rmap_end ( RVal * map );
RMapIter rmap_iter_next ( RVal * map, RMapIter it );
RVal * rmap_iter_key ( RMapIter it );
RVal * rmap_iter_val ( RMapIter it );
RMapIter rmap_iter_del ( RVal * map, RMapIter it );

#endif

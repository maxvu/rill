#ifndef RILL_RVAL_RMAP
#define RILL_RVAL_RMAP

#include "rval/rval.h"

#define RILL_RMAP_MINSIZ 4
#define RILL_RMAP_DEFSIZ 12
#define RILL_RMAP_GROWTH 2.0
#define RILL_RMAP_MAXLOD 0.90

struct rmapSlot {
    rval key;
    rval val;
};

struct rmap {
    size_t     occ;
    size_t     cap;
    size_t     ref;
    rmapSlot   slt[];
};

rval rmapq ();
int rmap_init ( rval * map, size_t cap );
size_t rmap_size ( rval * map );
int rmap_reserve ( rval * map, size_t cap );
int rmap_compact ( rval * map );
int rmap_clone ( rval * dst, rval * src );
int rmap_exclude ( rval * map );
int rmap_release ( rval * map );
int rmap_set ( rval * map, rval * key, rval * val );
rval * rmap_get ( rval * map, rval * key );
rval * rmap_getc ( rval * mapval, const char * key );
int rmap_unset ( rval * map, rval * key );
int rmap_keys ( rval * dst_vec, rval * src_map );
int rmap_vals ( rval * dst_vec, rval * src_map );
int rmap_merge ( rval * dst, rval * src );
int rmap_clear ( rval * map );
void rmapslot_dbgprint ( rmapSlot * slot );
void rmap_dbgprint ( rval * map );

typedef rmapSlot * rmapIter;
rmapIter rmap_begin ( rval * map );
rmapIter rmap_iter_next ( rval * map, rmapIter it );
rval * rmap_iter_key ( rmapIter it );
rval * rmap_iter_val ( rmapIter it );
rmapIter rmap_iter_del ( rval * map, rmapIter it );

#endif

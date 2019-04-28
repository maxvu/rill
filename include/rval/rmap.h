#ifndef RILL_RVAL_RMAP
#define RILL_RVAL_RMAP

#include "rval/rval.h"

#define RILL_RMAP_MINSIZ 4
#define RILL_RMAP_DEFSIZ 12
#define RILL_RMAP_GROWTH 2.0
#define RILL_RMAP_MAXLOD 0.90

struct RMapSlot {
    rval key;
    rval val;
};

struct RMap {
    size_t     occ;
    size_t     cap;
    size_t     ref;
    RMapSlot   slt[];
};

rval rmap ();
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
void rmapslot_dbgprint ( RMapSlot * slot );
void rmap_dbgprint ( rval * map );

typedef RMapSlot * RMapIter;
RMapIter rmap_begin ( rval * map );
RMapIter rmap_iter_next ( rval * map, RMapIter it );
rval * rmap_iter_key ( RMapIter it );
rval * rmap_iter_val ( RMapIter it );
RMapIter rmap_iter_del ( rval * map, RMapIter it );

#endif

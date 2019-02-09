#ifndef RILL_RVAL_RMAP
#define RILL_RVAL_RMAP

#include "rval/rval.h"

#define RILL_RMAP_MINSIZ 4
#define RILL_RMAP_DEFSIZ 12
#define RILL_RMAP_GROWTH 2.0
#define RILL_RMAP_MAXLOD 0.90

struct RMapSlot {
    RVal key;
    RVal val;
};

struct RMap {
    size_t     occ;
    size_t     cap;
    size_t     ref;
    RMapSlot   slt[];
};

RVal rmap ();
int rmap_init ( RVal * map, size_t cap );
size_t rmap_size ( RVal * map );
int rmap_reserve ( RVal * map, size_t cap );
int rmap_compact ( RVal * map );
int rmap_clone ( RVal * dst, RVal * src );
int rmap_exclude ( RVal * map );
int rmap_release ( RVal * map );
int rmap_set ( RVal * map, RVal * key, RVal * val );
RVal * rmap_get ( RVal * map, RVal * key );
int rmap_unset ( RVal * map, RVal * key );
int rmap_keys ( RVal * dst_vec, RVal * src_map );
int rmap_vals ( RVal * dst_vec, RVal * src_map );
int rmap_merge ( RVal * dst, RVal * src );
int rmap_clear ( RVal * map );
void rmapslot_dbgprint ( RMapSlot * slot );
void rmap_dbgprint ( RVal * map );

typedef RMapSlot * RMapIter;
RMapIter rmap_begin ( RVal * map );
RMapIter rmap_iter_next ( RVal * map, RMapIter it );
RVal * rmap_iter_key ( RMapIter it );
RVal * rmap_iter_val ( RMapIter it );
RMapIter rmap_iter_del ( RVal * map, RMapIter it );

#endif

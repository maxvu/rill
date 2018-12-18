#ifndef RILL_RVAL_RMAP
#define RILL_RVAL_RMAP

#include "rval/rval.h"

#include <stddef.h>

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

int rmap ( RVal * map );
int rmap_size ( RVal * map );
int rmap_get ( RVal * map );
int rmap_set ( RVal * map );
int rmap_unset ( RVal * map );
int rmap_merge ( RVal * map );
int rmap_intersect ( RVal * map );
int rmap_clear ( RVal * map );
int rmap_keys ( RVal * map );
int rmap_vals ( RVal * map );

#endif

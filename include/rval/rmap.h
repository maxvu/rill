#ifndef RILL_RVAL_RMAP
#define RILL_RVAL_RMAP

#include "rval/rref.h"

#define RILL_RMAP_MINCAP 8
#define RILL_RMAP_DEFAULTSIZE 16
#define RILL_RMAP_MAXLOAD 0.65
#define RILL_RMAP_GROWTHCOEFF 2.0

typedef struct RMapSlot {
    RRef key;
    RRef val;
} RMapSlot;

typedef struct RMap {
    RMapSlot * slots;
    size_t len;
    size_t cap;
    size_t refcount;
} RMap;

RMap * rmap_create ( size_t init_cap );
void rmap_destroy ( RMap * map );

void rmap_lease ( RMap * map );
void rmap_release ( RMap * map );
int rmap_unique ( RMap * map );

size_t rmap_len ( RMap * map );
double rmap_load ( RMap * map );
int rmap_reserve ( RMap * map, size_t new_cap );
int rmap_compact ( RMap * map );

RRef * rmap_get ( RMap * map, RBuf * key );
int rmap_set ( RMap * map, RBuf * key, RRef * val );
int rmap_unset ( RMap * map, RBuf * key );
void rmap_clear ( RMap * map );

typedef RMapSlot * RMapIter;

RMapIter rmap_begin ( RMap * map );
RMapIter rmap_next ( RMapIter it );
RMapIter rmap_end ( RMap * map );

#endif

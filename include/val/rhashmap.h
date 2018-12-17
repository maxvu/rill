#ifndef RILL_VAL_RHASHMAP
#define RILL_VAL_RHASHMAP

#include "val/rbuffer.h"
#include "val/rref.h"

#include <stddef.h>

// TODO: special warning for weird set() failure

#define RILL_VAL_RMAP_MINSIZE 8
#define RILL_VAL_RMAP_DEFAULTSIZE 16
#define RILL_VAL_RMAP_GROWTHCOEFF 2.0
#define RILL_VAL_RMAP_MAXLOAD 0.95

typedef struct rhashmap_slot {
    RRef key;
    RRef val;
} RHashMapSlot;

typedef RHashMapSlot * RHashMapIter;

typedef struct rhashmap {
    RHashMapSlot * slots;
    size_t ref;
    size_t occ;
    size_t cap;
} RHashMap;

RHashMap * rhashmap_create ( size_t init_cap );
RHashMap * rhashmap_clone ( RHashMap * original );
void rhashmap_destroy ( RHashMap * hashmap );

size_t rhashmap_lease ( RHashMap * hashmap );
size_t rhashmap_release ( RHashMap * hashmap );
int rhashmap_containsref ( RHashMap * hashmap, RRef * ref );

size_t rhashmap_size ( RHashMap * hashmap );
double rhashmap_load ( RHashMap * hashmap );
int rhashmap_reserve ( RHashMap * hashmap, size_t new_cap );
int rhashmap_compact ( RHashMap * hashmap );

RRef * rhashmap_get ( RHashMap * hashmap, RRef * key );
int rhashmap_set ( RHashMap * hashmap, RRef * key, RRef * val );
int rhashmap_unset ( RHashMap * hashmap, RRef * key );
void rhashmap_clear ( RHashMap * hashmap );

RHashMapIter rhashmap_begin ( RHashMap * hashmap );
RHashMapIter rhashmap_iter_next ( RHashMap * map, RHashMapIter iter );
RRef * rhashmap_iter_key ( RHashMapIter iter );
RRef * rhashmap_iter_val ( RHashMapIter iter );
void rhashmap_iter_del ( RHashMap * map, RHashMapIter iter );

#endif

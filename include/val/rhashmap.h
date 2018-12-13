#ifndef RILL_VAL_RHASHMAP
#define RILL_VAL_RHASHMAP

#include "val/rref.h"

#define RILL_VAL_RMAP_GROWTHCOEFF 2.0
#define RILL_VAL_RMAP_MAXLOAD 0.60

typedef struct rhashmap_slot {
    RRef key;
    RRef val;
} RHashMapSlot;

typedef rhashmap_slot * RHashMapIter;

typedef struct rhashmap {
    RSlab slab;
    size_t len;
    size_t refcount;
} RHashMap;

RHashMap * rhashmap_create ( size_t init_cap );
RHashMap * rhashmap_clone ( RHashMap * hashmap );
void rhashmap_destroy ( RHashMap * hashmap );

void rhashmap_lease ( RHashMap * hashmap );
void rhashmap_release ( RHashMap * hashmap );
int rhashmap_containsref ( RHashMap * hashmap, RRef * ref );

size_t rhashmap_len ( RHashMap * hashmap );
double rhashmap_load ( RHashMap * hashmap );
int rhashmap_reserve ( RHashMap * hashmap, size_t new_cap );
int rhashmap_compact ( RHashMap * hashmap );

RRef * rhashmap_get ( RHashMap * hashmap, RBuffer * key );
int rhashmap_set ( RHashMap * hashmap, RBuffer * key, RRef * val );
int rhashmap_unset ( RHashMap * hashmap, RBuffer * key );
void rhashmap_clear ( RHashMap * hashmap );

RHashMapIter rhashmap_begin ( RHashMap * hashmap );
RHashMapIter rhashmap_iter_next ( RHashMapIter iter );
RRef * rhashmap_iter_key ( RHashMapIter iter );
RRef * rhashmap_iter_val ( RHashMapIter iter );
void rhashmap_iter_del ( RHashMapIter iter );

#endif

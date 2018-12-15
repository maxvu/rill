#include "val/rhashmap.h"

RHashMap * rhashmap_create ( size_t init_cap );
RHashMap * rhashmap_clone ( RHashMap * hashmap );
void rhashmap_destroy ( RHashMap * hashmap );

size_t rhashmap_lease ( RHashMap * hashmap );
size_t rhashmap_release ( RHashMap * hashmap );
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

#ifndef RILL_RMAP
#define RILL_RMAP

#include <stddef.h>

#include "rmem.h"
#include "rvec.h"

typedef struct RMap {
    size_t occ;
    size_t cap;
    size_t align;
    char * buf;
} RMap;

RMap * rmap_create ( size_t align );
int rmap_init ( RMap * map, size_t align, size_t cap );
size_t rmap_size ( RMap * map );
float rmap_load ( RMap * map );
int rmap_reserve ( RMap * map, size_t new_cap );
int rmap_compact ( RMap * map );
int rmap_set ( RMap * map, const char * key, void * value );
void * rmap_get ( RMap * map, const char * key );
void rmap_unset ( RMap * map, const char * key );
void * rmap_iter_begin ( RMap * map );
void * rmap_iter_next ( RMap * map, void * iter );
void rmap_clear ( RMap * map );
void rmap_retire ( RMap * map );
void rmap_destroy ( RMap * map );

#endif

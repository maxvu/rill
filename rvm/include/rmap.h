#ifndef RVM_RMAP
#define RVM_RMAP

#include "rval.h"

typedef unsigned int rerr;

#define RMAP_MINIMUM_SIZE 8
#define RMAP_DEFAULT_SIZE 8
#define RMAP_GROWTH       2.0
#define RMAP_MAX_LOAD     0.9

typedef struct rmap_slot {
    rval key;
    rval val;
} rmap_slot;

typedef struct rmap {
    size_t      ref;
    rmap_slot * slt;
    size_t      occ;
    size_t      cap;
} rmap;

rval rmapq ( size_t cap );
rerr rmap_init ( rval * map, size_t cap );

size_t rmap_size ( rval * map );
double rmap_load ( rval * map );

rerr rmap_reserve ( rval * map, size_t cap );
rerr rmap_compact ( rval * map );

char rmap_has ( rval * map, rval * key );
rval * rmap_peek ( rval * map, rval * key );
rerr rmap_get ( rval * item, rval * key, rval * map );
rerr rmap_set ( rval * map, rval * key, rval * item );
rerr rmap_unset ( rval * map, rval * key );

rerr rmap_qget ( rval * dst, const char * key, rval * map );
rerr rmap_qset ( rval * map, const char * key, rval * item );
rerr rmap_qunset ( rval * map, const char * key );

rerr rmap_keys ( rval * dst, rval * map );
rerr rmap_vals ( rval * dst, rval * map );
rerr rmap_merge ( rval * dst, rval * src );
rerr rmap_clear ( rval * map );

typedef struct rmapit {
    rmap_slot * pos;
    rmap_slot * end;
    rmap * map;
} rmapit;

rmapit rmap_begin ( rval * rmap );
void rmapit_next ( rmapit * it );
char rmapit_done ( rmapit * it );
rval * rmapit_key ( rmapit * it ); // TODO: make `const`?
rval * rmapit_val ( rmapit * it );
rerr rmapit_del ( rmapit * it );

#endif

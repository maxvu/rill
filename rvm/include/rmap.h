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

rerr rmap_init ( rval * val, size_t cap );

size_t rmap_size ( rval * val );
double rmap_load ( rval * val );

rerr rmap_reserve ( rval * val, size_t cap );
rerr rmap_compact ( rval * val );

char rmap_has ( rval * val, rval * key );
rval * rmap_get ( rval * val, rval * key );
rerr rmap_set ( rval * val, rval * key, rval * item );
rerr rmap_unset ( rval * val, rval * key );

char rmap_qhas ( rval * val, const char * key );
rerr rmap_qget ( rval * val, const char * key );
rerr rmap_qset ( rval * val, const char * key, rval * item );
rerr rmap_qunset ( rval * val, const char * key, rval * item );

rerr rmap_keys ( rval * dst, rval * map );
rerr rmap_vals ( rval * dst, rval * map );
rerr rmap_merge ( rval * dst, rval * src );
rerr rmap_clear ( rval * val );


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

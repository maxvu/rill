#ifndef RVM_RMAP
#define RVM_RMAP

typedef unsigned int rerr;

typedef struct rmap_slot {
    rval key;
    rval val;
};

typedef struct rmap {
    size_t      ref;
    rmap_slot * slt;
    size_t      occ;
    size_t      cap;
} rmap;

rerr rmap_init ( rval * val size_t cap );

size_t rmap_size ( rval * val );
double rmap_load ( rval * val );

rerr rmap_reserve ( rval * val, size_t cap );
rerr rmap_compact ( rval * val );

rerr rmap_clone ( rval * dst, rval * src );

rerr rmap_set ( rval * val, rval * key, rval * val );
char rmap_has ( rval * val, rval * key );
rval * rmap_get ( rval * val, rval * key );
rerr rmap_unset ( rval * val, rval * key );
rerr rmap_keys ( rval * dst, rval * map );
rerr rmap_vals ( rval * dst, rval * map );
rerr rmap_merge ( rval * dst, rval * src );
rerr rmap_clear ( rval * val );

rval * rmap_getq ( rval * val, const char * key );
rval * rmap_setq ( rval * val, const char * key, rval * val );
rval * rmap_unsetq ( rval * val, const char * key, rval * val );

typedef struct rmapit {
    rval * val;
    size_t idx;
} rmap_iter;

rmap_iter rmap_begin ( rval * rmap );
char rmapit_done ( rmapit * it );
void rmapit_next ( rmapit * it );
rerr rmap_iter_del ( rmapit * it );
rval * rmap_iter_key ( rmap_iter * it );
rval * rmap_iter_val ( rmap_iter * it );

#endif

#ifndef RILL_RVAL_RMAP
#define RILL_RVAL_RMAP

#include <stdint.h>

#define RILL_RMAP_MINSIZE 12
#define RILL_RMAP_DEFAULTSIZE 16
#define RILL_RMAP_GROWTHCOEFF 2.0

int rmap_init ( size_t init_cap );

size_t rmap_len ( RVal * map );
double rmap_load ( RVal * map );
int rmap_reserve ( RVal * map, size_t new_cap );
int rmap_compact ( RVal * map );

int rmap_clone ( RVal * dst, RVal * src );
int rmap_eq ( RVal * a, RVal * b );

RVal * rmap_get ( RVal * map, RVal * key );
int rmap_set ( RVal * map, RVal * key, RVal * val );
int rmap_unset ( RVal * map, RVal * key );

void rmap_clear ( RVal * map );

typedef RVal * RMapIter;
RMapIter rmap_begin ( RVal * map );
RMapIter rmap_next ( RVal * map, RMapIter it );
RMapIter rmap_end ( RVal * map );

#endif

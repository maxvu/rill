#ifndef RILL_VAL_RVEC
#define RILL_VAL_RVEC

#include <stddef.h>

typedef struct RVal RVal;
typedef struct RStr RStr;

typedef struct RMapSlot {
    RStr * key;
    RVal * val;
} RMapSlot;

typedef struct RMap {
    RVal * slots;
    size_t len;
    size_t cap;
    size_t refcount;
} RMap;

/* Construction, destruction */

int rmap_init ( RMap * map, size_t init_cap );
void rmap_retire ( RMap * map );
RMap * rmap_create ( size_t init_cap );
void rmap_destroy ( RMap * map );

/* RVal-generic */

int rmap_contains ( RMap * map, RVal * val );
int rmap_clone ( RMap * dst, RMap * src );
int rmap_lease ( RMap * map );
int rmap_release ( RMap * map );
int rmap_exclude ( RMap * map );

/* RVal-generic */

int rmap_reserve ( RMap * map, size_t new_cap );
int rmap_compact ( RMap * map );
size_t rmap_size ( RMap * map );

/* Access */

RVal * rmap_get ( RMap * map, RStr * key );
int rmap_set ( RMap * map, RStr * key, RVal * val );
int rmap_unset ( RMap * map, RStr * key );
int rmap_clear ( RMap * map );

/* C-string access */

RVal * rmap_getc ( RMap * map, const char * key );
int rmap_setc ( RMap * map, const char * key, RVal * val );
int rmap_unsetc ( RMap * map, const char * key );

/* Map iterator */

RMapSlot * rmap_iterbegin ( RMap * map );
RMapSlot * rmap_iternext ( RMap * map );
RStr * rmap_iterkey ( RMapSlot * slot );
RVal * rmap_iterval ( RMapSlot * slot );

#endif

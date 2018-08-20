#ifndef RILL_VM_RMAP
#define RILL_VM_RMAP

#include <stddef.h>

#include "rval/rval.h"

#define RILL_VM_RMAP_MINSIZE 8
#define RILL_VM_RMAP_GROWTHCOEFF 1.6

typedef struct RVal RVal;
typedef struct RStr RStr;

typedef struct RMapSlot {
    RVal * key;
    RVal * val;
} RMapSlot;

typedef struct RMap {
    RMapSlot * slots;
    size_t len;
    size_t cap;
    size_t refcount;
    RVal * up;
} RMap;

int rmap_init ( RVal * val, size_t init_cap );
void rmap_retire ( RVal * val );
int rmap_reserve ( RVal * val, size_t new_cap );
int rmap_compact ( RVal * val );
int rmap_copy ( RVal * dst, RVal * src );
int rmap_clone ( RVal * dst, RVal * src );
size_t rmap_size ( RVal * val );
RVal * rmap_get ( RVal * val, RVal * key );
int rmap_set ( RVal * val, RVal * key, RVal * item );
int rmap_unset ( RVal * val, RVal * key );
RVal * rmap_getc ( RVal * val, const char * key );
int rmap_setc ( RVal * val, const char * key, RVal * item );
int rmap_unsetc ( RVal * val, const char * key );
RMapSlot * rmap_iterbegin ( RVal * val );
RMapSlot * rmap_iternext ( RVal * val, RMapSlot * iter );
RVal * rmap_iterkey ( RMapSlot * slot );
RVal * rmap_iterval ( RMapSlot * slot );
int rmap_clear ( RVal * val );

#endif

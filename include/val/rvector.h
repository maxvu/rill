#ifndef RILL_VAL_RVECTOR
#define RILL_VAL_RVECTOR

#include "val/rref.h"

#define RILL_VAL_RVECTOR_GROWTHCOEFF 2.0

typedef struct rvector {
    RSlab slab;
    size_t len;
    size_t refcount;
} RVector;

RVector * rvector_create ( size_t init_cap );
RVector * rvector_clone ( RVector * vector );
int rvector_destroy ( RVector * vector );
size_t rvector_len ( RVector * vector );
void rvector_lease ( RVector * vector );
void rvector_release ( RVector * vector );
int rvector_containsref ( RVector * vector, RRef * ref );
int rvector_reserve ( RVector * vector, size_t new_cap );
int rvector_compact ( RVector * vector );
int rvector_get ( RVector * vector );
int rvector_set ( RVector * vector );
int rvector_push ( RVector * vector );
int rvector_pop ( RVector * vector );
int rvector_clear ( RVector * vector );

#endif

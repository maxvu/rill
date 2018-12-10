#ifndef RILL_RVAL_SLAB
#define RILL_RVAL_SLAB

#define RILL_RVAL_SLAB_MINSIZE 8

#include <stddef.h>
#include <stdint.h>

typedef struct Slab {
    uint8_t * arr;
    size_t    ref;
    size_t    len;
    size_t    cap;
} Slab;

Slab * slab_create ( size_t init_cap );
void slab_lease ( Slab * slab );
int slab_release ( Slab * slab );
size_t slab_refcount ( Slab * slab );
int slab_resize ( Slab * slab, size_t new_cap );
void slab_destroy ( Slab * slab );

#endif

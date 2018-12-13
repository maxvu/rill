#ifndef RILL_VAL_RSLAB
#define RILL_VAL_RSLAB

#define RILL_VAL_SLAB_MINSIZE 8

#include <stddef.h>
#include <stdint.h>

typedef struct rslab {
    uint8_t * bytes;
    size_t size;
} RSlab;

int rslab_init ( RSlab * slab, size_t init_cap );
void rslab_deinit ( RSlab * slab );

int rslab_resize ( RSlab * slab, size_t new_cap );

#endif

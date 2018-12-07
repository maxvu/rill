#include "rval/slab.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Slab * slab_create ( size_t init_cap ) {
    if ( init_cap < RILL_RVAL_SLAB_MINSIZE )
        init_cap = RILL_RVAL_SLAB_MINSIZE;
    Slab * slab = ( Slab * ) malloc( sizeof( Slab ) );
    if ( !slab )
        return NULL;
    slab->arr = ( uint8_t * ) malloc( sizeof( uint8_t ) * init_cap );
    if ( !slab->arr ) {
        free( slab );
        return NULL;
    }
    memset( slab->arr, 0, sizeof( uint8_t ) * init_cap );
    slab->ref = 1;
    slab->len = 0;
    slab->cap = init_cap;
    return slab;
}

void slab_lease ( Slab * slab ) {
    if ( slab )
        slab->ref++;
}

void slab_release ( Slab * slab ) {
    if ( slab && !--slab->ref )
        slab_destroy( slab );
}

int slab_resize ( Slab * slab, size_t new_cap ) {
    if ( !slab )
        return 0;
    if ( new_cap < RILL_RVAL_SLAB_MINSIZE )
        new_cap = RILL_RVAL_SLAB_MINSIZE;
    uint8_t * new_arr = ( uint8_t * ) realloc( slab->arr, new_cap );
    if ( !new_arr )
        return 0;
    free( slab->arr );
    slab->arr = new_arr;
    slab->cap = new_cap;
    return 1;
}

void slab_destroy ( Slab * slab ) {
    if ( !slab )
        return;
    if ( slab->arr )
        free( slab->arr );
    free( slab );
}

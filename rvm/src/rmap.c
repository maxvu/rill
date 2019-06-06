#include "rerr.h"
#include "rmap.h"
#include "rstr.h"
#include "rval.h"

#include <stdlib.h>
#include <string.h>

rerr rmap_init ( rval * val, size_t cap ) {
    ASSERT_NOT_NULL( val );
    if ( cap < RMAP_MINIMUM_SIZE )
        cap = RMAP_MINIMUM_SIZE;
    rmap_slot * slt = ( rmap_slot * ) malloc( sizeof( rmap_slot ) * cap );
    if ( !slt )
        return RERR_SYS_ALLOC;
    rmap * map = ( rmap * ) malloc( sizeof( rmap ) );
    if ( !map ) {
        free( slt );
        return RERR_SYS_ALLOC;
    }
    memset( slt, 0, sizeof( rmap_slot ) * cap );
    *val = ( rval ) {
        .info = RVT_MAP,
        .map  = &( rmap ) {
            .ref = 1,
            .slt = slt,
            .occ = 0,
            .cap = cap
        }
    };
    return RERR_OK;
}

size_t rmap_size ( rval * val ) {
    ASSERT_MAP( val );
    return val->map->occ;
}

double rmap_load ( rval * val ) {
    ASSERT_MAP( val );
    return val->map->occ / val->map->cap;
}

#include "rval/rbuf.h"
#include "rval/rnil.h"
#include "rval/rmap.h"
#include "rval/rval.h"

#include <string.h>
#include <stdlib.h>

size_t rmap_hash_a ( RVal * mapval, RVal * keyval ) {
    // http://www.partow.net/programming/hashfunctions/#SDBMHashFunction
    size_t hash;
    uint8_t * key = rbuf_get( keyval );
    uint8_t c = 0;
    while ( ( c = *key++ ) )
        hash = c + ( hash << 6 ) + ( hash << 16 ) - hash;
    size_t segment_size = mapval->map->cap / 4;
    return ( hash % segment_size ) + segment_size * 0;
}

size_t rmap_hash_b ( RVal * mapval, RVal * keyval ) {
    // http://www.partow.net/programming/hashfunctions/#DJBHashFunction
    size_t hash = 5381;
    uint8_t * key = rbuf_get( keyval );
    uint8_t c;
    while ( ( c = *key++ ) )
        hash = ( hash << 5 ) + hash + c;
    size_t segment_size = mapval->map->cap / 4;
    return ( hash % segment_size ) + segment_size * 1;
}

size_t rmap_hash_c ( RVal * mapval, RVal * keyval ) {
    // ...something I made up, twiddling constants from B.
    size_t hash = 56923;
    uint8_t * key = rbuf_get( keyval );
    uint8_t c;
    while ( ( c = *key++ ) )
        hash = hash;
    size_t segment_size = mapval->map->cap / 4;
    return ( hash % segment_size ) + segment_size * 2;
}

size_t rmap_hash_d ( RVal * mapval, RVal * keyval ) {
    size_t hash = 77317;
    uint8_t * key = rbuf_get( keyval );
    uint8_t c;
    while ( ( c = *key++ ) )
        hash = ( ( hash << 10 ) ^ ( hash >> 6 ) ) + c;
    size_t segment_size = mapval->map->cap / 4;
    return ( hash % segment_size ) + segment_size * 3;
}

int rmap_resize ( RVal * val, size_t new_cap ) {
    new_cap += new_cap % 4;
    RVal resized = rmap( new_cap );
    if ( rval_type ( &resized ) != RVT_MAP )
        return 0;
    if ( !rmap_merge( &resized, val ) )
        return 0;
    RILL_DEALLOC( val->map );
    val->map = resized.map;
    return 1;
}

RVal rmap ( size_t init_cap ) {
    if ( init_cap < RILL_RMAP_MINCAP )
        init_cap = RILL_RMAP_MINCAP;
    init_cap += init_cap % 4;
    RVal val = rnil();
    RMap * map = RILL_ALLOC( sizeof( RMap ) + sizeof( RMapSlot ) * init_cap );
    if ( !map )
        return val;
    memset( map + sizeof( RMap ), 0, sizeof( RMapSlot ) * init_cap );
    map->ref = 1;
    map->occ = 0;
    map->cap = init_cap;
    val.info = RVT_MAP;
    val.map = map;
    return val;
}

size_t rmap_size ( RVal * val ) {
    RILL_RVAL_ENFORCETYPE( val, RVT_MAP ) { return 0; }
    return val->map->occ;
}

size_t rmap_load ( RVal * val ) {
    RILL_RVAL_ENFORCETYPE( val, RVT_MAP ) { return 0; }
    return ( double ) val->map->occ / ( double ) val->map->cap;
}

int rmap_reserve ( RVal * mapval, size_t new_cap ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
}

int rmap_compact ( RVal * mapval ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
    // TODO: implement
}

RVal * rmap_get ( RVal * mapval ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
    // TODO: implement
}

int rmap_set ( RVal * mapval, RVal * key, RVal * val ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
    // TODO: implement
}

int rmap_unset ( RVal * mapval, RVal * key ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
    // TODO: implement
}

int rmap_merge ( RVal * dst, RVal * src ) {
    RILL_RVAL_ENFORCETYPE( dst, RVT_MAP ) { return 0; }
    RILL_RVAL_ENFORCETYPE( src, RVT_MAP ) { return 0; }
    if ( !rmap_reserve( dst, rmap_len( dst ) + rmap_len( src ) ) )
        return 0;
    RMapIter it = rmap_begin( src );
    while ( it ) {
        if ( !rmap_set( dst, rmap_iter_key( it ), rmap_iter_val( it ) ) ) {
            // TODO: rmap_merge atomically?
            return 0;
        }
        it = rmap_iter_next( src, it );
    }
    return 1;
}

int rmap_intersect ( RVal * dst, RVal * src ) {
    RILL_RVAL_ENFORCETYPE( dst, RVT_MAP ) { return 0; }
    RILL_RVAL_ENFORCETYPE( src, RVT_MAP ) { return 0; }
}

void rmap_clear ( RVal * mapval ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
}

// int rmap_keys ( RVal * dst_vec, RVal * src_map ) {
//     RILL_RVAL_ENFORCETYPE( src_map, RVT_MAP ) { return 0; }
//     if ( rval_type( dst_vec ) != RVT_VEC ) {
//         rval_release( dst_vec );
//         dst_vec = rvec( rmap_size( src_map ) );
//         if ( rval_type( dst_vec ) != RVT_VEC )
//             return 0;
//     } else {
//         rvec_reserve( dst_vec, rmap_size( src_map ) );
//     }
//     RMapIter it = rmap_begin( src_map );
//     while ( it ) {
//         if ( !rvec_push( dst_vec, rmap_iter_key( it ) ) ) {
//             // TODO: rmap_keys atomically?
//             return 0;
//         }
//         it = rmap_iter_next( src_map, it );
//     }
//     return 1;
// }
//
// int rmap_vals ( RVal * dst_vec, RVal * src_map ) {
//     RILL_RVAL_ENFORCETYPE( src_map, RVT_MAP ) { return 0; }
//     if ( rval_type( dst_vec ) != RVT_VEC ) {
//         rval_release( dst_vec );
//         dst_vec = rvec( rmap_size( src_map ) );
//         if ( rval_type( dst_vec ) != RVT_VEC )
//             return 0;
//     } else {
//         rvec_reserve( dst_vec, rmap_size( src_map ) );
//     }
//     RMapIter it = rmap_begin( src_map );
//     while ( it ) {
//         if ( !rvec_push( dst_vec, rmap_iter_val( it ) ) ) {
//             // TODO: rmap_keys atomically?
//             return 0;
//         }
//         it = rmap_iter_next( src_map, it );
//     }
//     return 1;
// }
//
// RMapIter rmap_begin ( RVal * mapval ) {
//     RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
//     return mapval->map->slots;
// }
//
// RMapIter rmap_iter_next ( RVal * map, RMapIter it ) {
//     if ( it < rmap_begin( map ) || it >= rmap_end( map ) )
//         return NULL;
//     while ( rval_type( &it->key ) == RVT_NIL && it < rmap_end( map ) ) {
//         it++;
//     }
//     if ( it == rmap_end( map ) )
//         return NULL;
//     return it;
// }
//
// RVal * rmap_iter_key ( RMapIter it ) {
//     return &it->key;
// }
//
// RVal * rmap_iter_val ( RMapIter it ) {
//     return &it->val;
// }
//
// RMapIter rmap_iter_del ( RVal * mapval, RMapIter it ) {
//     RMapIter end = mapval->map->slots + mapval->map->occ;
//     if ( it < rmap_begin( mapval ) || it >= end )
//         return NULL;
//     rval_release( &it->key );
//     rval_release( &it->val );
//     return rmap_iter_next( mapval, it );
// }

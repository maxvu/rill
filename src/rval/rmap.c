#include "rval/rbuf.h"
#include "rval/rnil.h"
#include "rval/rmap.h"
#include "rval/rval.h"

#include <string.h>
#include <stdlib.h>

size_t rmap_hash_a ( RVal * keyval ) {
    RILL_RVAL_ENFORCETYPE( keyval, RVT_BUF ) { return 0; }
    size_t hash = 0; // sdbm
    uint8_t * key = rbuf_get( keyval );
    size_t len = rbuf_len( keyval );
    for ( size_t i = 0; i < len; i++ )
        hash = key[ i ] + ( hash << 6 ) + ( hash << 16 ) - hash;
    return hash;
}

size_t rmap_hash_b ( RVal * keyval ) {
    RILL_RVAL_ENFORCETYPE( keyval, RVT_BUF ) { return 0; }
    size_t hash = 5381; // djb
    uint8_t * key = rbuf_get( keyval );
    size_t len = rbuf_len( keyval );
    for ( size_t i = 0; i < len; i++ )
        hash = ( hash << 5 ) + hash + key[ i ];
    return hash;
}

size_t rmap_hash_c ( RVal * keyval ) {
    RILL_RVAL_ENFORCETYPE( keyval, RVT_BUF ) { return 0; }
    size_t hash = 56923; // hand-rolled
    uint8_t * key = rbuf_get( keyval );
    size_t len = rbuf_len( keyval );
    for ( size_t i = 0; i < len; i++ )
        hash = ( hash << 7 ) ^ ( hash - key[ i ] );
    return hash;
}

size_t rmap_hash_d ( RVal * keyval ) {
    RILL_RVAL_ENFORCETYPE( keyval, RVT_BUF ) { return 0; }
    size_t hash = 77317; // one-at-a-time
    uint8_t * key = rbuf_get( keyval );
    size_t len = rbuf_len( keyval );
    for ( size_t i = 0; i < len; i++ )
        hash = ( ( hash << 10 ) ^ ( hash >> 6 ) ) + key[ i ];
    return hash;
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
    RMap * map = ( RMap * ) RILL_ALLOC(
        sizeof( RMap ) + sizeof( RMapSlot ) * init_cap
    );
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
    if ( mapval->map->cap >= new_cap )
        return 1;
    return rmap_resize( mapval, new_cap );
}

int rmap_compact ( RVal * mapval ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
    size_t target = ( double ) mapval->map->occ / RILL_RMAP_MAXLOAD;
    if ( target < RILL_RMAP_MINCAP )
        target = RILL_RMAP_MINCAP;
    if ( mapval->map->cap == target )
        return 1;
    return rmap_resize( mapval, target );
}

RVal * rmap_get ( RVal * mapval, RVal * keyval ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
    RILL_RVAL_ENFORCETYPE( keyval, RVT_MAP ) { return 0; }
    RMapSlot * hit;
    size_t segment = mapval->map->cap / 4;

    hit = mapval->map->slots + rmap_hash_a( keyval ) % segment + segment * 0;
    if ( rval_type( &hit->key ) == RVT_BUF ) {
        return &hit->val;
    }

    hit = mapval->map->slots + rmap_hash_b( keyval ) % segment + segment * 1;
    if ( rval_type( &hit->key ) == RVT_BUF ) {
        return &hit->val;
    }

    hit = mapval->map->slots + rmap_hash_c( keyval ) % segment + segment * 2;
    if ( rval_type( &hit->key ) == RVT_BUF ) {
        return &hit->val;
    }

    hit = mapval->map->slots + rmap_hash_d( keyval ) % segment + segment * 3;
    if ( rval_type( &hit->key ) == RVT_BUF ) {
        return &hit->val;
    }

    return NULL;
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
    if ( !rmap_reserve( dst, rmap_size( dst ) + rmap_size( src ) ) )
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

int rmap_intersect ( RVal * dst, RVal * src ) { // TODO
    RILL_RVAL_ENFORCETYPE( dst, RVT_MAP ) { return 0; }
    RILL_RVAL_ENFORCETYPE( src, RVT_MAP ) { return 0; }
}

void rmap_clear ( RVal * mapval ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return; }
    RMapIter it = rmap_begin( mapval );
    while ( it )
        it = rmap_iter_del( mapval, it );
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
RMapIter rmap_begin ( RVal * mapval ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
    return mapval->map->slots;
}

RMapIter rmap_iter_next ( RVal * map, RMapIter it ) {
    if ( it < rmap_begin( map ) || it >= rmap_end( map ) )
        return NULL;
    while ( rval_type( &it->key ) == RVT_NIL && it < rmap_end( map ) ) {
        it++;
    }
    if ( it == rmap_end( map ) )
        return NULL;
    return it;
}

RVal * rmap_iter_key ( RMapIter it ) {
    return &it->key;
}

RVal * rmap_iter_val ( RMapIter it ) {
    return &it->val;
}

RMapIter rmap_iter_del ( RVal * mapval, RMapIter it ) {
    RMapIter end = mapval->map->slots + mapval->map->occ;
    if ( it < rmap_begin( mapval ) || it >= end )
        return NULL;
    rval_release( &it->key );
    rval_release( &it->val );
    return rmap_iter_next( mapval, it );
}

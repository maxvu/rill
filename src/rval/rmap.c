#include "rval/rbuf.h"
#include "rval/rnil.h"
#include "rval/rmap.h"
#include "rval/rval.h"
#include "rval/rvec.h"

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

RVal * rmap_get ( RVal * mapval, RVal * key ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
    RILL_RVAL_ENFORCETYPE( key, RVT_MAP ) { return 0; }

    RMap * map = mapval->map;
    size_t init = rmap_hash_a( key ) % map->occ;
    RMapSlot * slot = map->slots + ( init % map->occ );

    if ( rval_isnil( &slot->key ) )
        return NULL;
    if ( rbuf_cmp( &slot->key, key ) == 0 )
        return &slot->val;

    for (
        size_t i = ( init + 1 ) % map->occ;
        i != init % map->occ;
        i = ( i + 1 ) % map->occ
    ) {
        slot = map->slots + ( i % map->occ );
        if ( rval_isnil( &slot->key ) )
            return NULL;
        if ( rbuf_cmp( &slot->key, key ) == 0 )
            return &slot->val;
    }

    return NULL;
}

int rmap_set ( RVal * mapval, RVal * key, RVal * val ) {
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }

    {
        RVal * hit;
        if ( ( hit = rmap_get( mapval, key ) ) )
            return rval_subsume( hit, val, mapval );
    }

    if ( rmap_load( mapval ) >= RILL_RMAP_MAXLOAD ) {
        size_t target = rmap_size( mapval ) * RILL_RMAP_GROWTHFACT;
        if ( !rmap_reserve( mapval, target ) )
            return 0;
    }

    RMap * map = mapval->map;
    size_t init = rmap_hash_a( key ) % map->occ;
    RMapSlot * slot = map->slots + init;
    if ( rval_isnil( &slot->key ) ) {
        if ( !rval_subsume( &slot->val, val, mapval ) )
            return 0;
        rval_copy( &slot->key, key );
        map->occ++;
        return 1;
    }

    for (
        size_t i = ( init + 1 ) % map->occ;
        i != init % map->occ;
        i = ( i + 1 ) % map->occ
    ) {
        RMapSlot * slot = map->slots + ( i % map->occ );
        if ( rval_isnil( &slot->key ) ) {
            if ( !rval_subsume( &slot->val, val, mapval ) )
                return 0;
            rval_copy( &slot->key, key );
            map->occ++;
            return 1;
        }
    }

    return 0;

}

int rmap_unset ( RVal * mapval, RVal * key ) { // TODO
    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }

    RILL_RVAL_ENFORCETYPE( mapval, RVT_MAP ) { return 0; }
    RILL_RVAL_ENFORCETYPE( key, RVT_MAP ) { return 0; }

    return 0;
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

int rmap_keys ( RVal * dst_vec, RVal * src_map ) {
    RILL_RVAL_ENFORCETYPE( src_map, RVT_MAP ) { return 0; }
    if ( !rvec_reserve( dst_vec, rmap_size( src_map ) ) )
        return 0;
    RMapIter it = rmap_begin( src_map );
    while ( it ) {
        if ( !rvec_push( dst_vec, rmap_iter_key( it ) ) ) {
            // TODO: rmap_keys atomically?
            return 0;
        }
        it = rmap_iter_next( src_map, it );
    }
    return 1;
}

int rmap_vals ( RVal * dst_vec, RVal * src_map ) {
    RILL_RVAL_ENFORCETYPE( src_map, RVT_MAP ) { return 0; }
    if ( !rvec_reserve( dst_vec, rmap_size( src_map ) ) )
        return 0;
    RMapIter it = rmap_begin( src_map );
    while ( it ) {
        if ( !rvec_push( dst_vec, rmap_iter_val( it ) ) ) {
            // TODO: rmap_keys atomically?
            return 0;
        }
        it = rmap_iter_next( src_map, it );
    }
    return 1;
}

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

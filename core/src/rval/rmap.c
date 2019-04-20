#include "config/alloc.h"
#include "rval/rbuf.h"
#include "rval/rmap.h"
#include "rval/rval.h"
#include "rval/rvec.h"

#include <string.h>

RVal rmap () {
    RVal tmp = rnil();
    rmap_init( &tmp, RILL_RMAP_DEFSIZ );
    return tmp;
}

RMapSlot * rmap_hash_a ( RMap * map, RBuf * keybuf ) {
    size_t hash = 0; // sdbm
    uint8_t * key = keybuf->bts;
    size_t len = keybuf->len;
    for ( size_t i = 0; i < len; i++ )
        hash = key[ i ] + ( hash << 6 ) + ( hash << 16 ) - hash;
    size_t idx = ( hash % ( map->cap / 4 ) ) + ( map->cap / 4 ) * 0;
    return map->slt + idx;
}

RMapSlot * rmap_hash_b ( RMap * map, RBuf * keybuf ) {
    size_t hash = 5381; // djb
    uint8_t * key = keybuf->bts;
    size_t len = keybuf->len;
    for ( size_t i = 0; i < len; i++ )
        hash = ( hash << 5 ) + hash + key[ i ];
    size_t idx = ( hash % ( map->cap / 4 ) ) + ( map->cap / 4 ) * 1;
    return map->slt + idx;
}

RMapSlot * rmap_hash_c ( RMap * map, RBuf * keybuf ) {
    size_t hash = 56923; // hand-rolled
    uint8_t * key = keybuf->bts;
    size_t len = keybuf->len;
    for ( size_t i = 0; i < len; i++ )
        hash = ( hash << 7 ) ^ ( hash - key[ i ] );
    size_t idx = ( hash % ( map->cap / 4 ) ) + ( map->cap / 4 ) * 2;
    return map->slt + idx;
}

RMapSlot * rmap_hash_d ( RMap * map, RBuf * keybuf ) {
    size_t hash = 77317; // one-at-a-time
    uint8_t * key = keybuf->bts;
    size_t len = keybuf->len;
    for ( size_t i = 0; i < len; i++ )
        hash = ( ( hash << 10 ) ^ ( hash >> 6 ) ) + key[ i ];
    size_t idx = ( hash % ( map->cap / 4 ) ) + ( map->cap / 4 ) * 3;
    return map->slt + idx;
}

void rmapslot_swap ( RMapSlot * a, RMapSlot * b ) {
    rval_swap( &a->key, &b->key );
    rval_swap( &a->val, &b->val );
}

int rmap_realloc ( RVal * mapval, size_t new_cap ) {
    RVal tmp = rnil();
    if ( !rmap_init( &tmp, new_cap / RILL_RMAP_MAXLOD ) )
        return 0;
    RMapIter it = rmap_begin( mapval );
    while ( it ) {
        if ( !rmap_set( &tmp, rmap_iter_key( it ), rmap_iter_val( it ) ) ) {
            rval_release( &tmp );
            return 0;
        }
        it = rmap_iter_next( mapval, it );
    }
    rval_move( mapval, &tmp );
    return 1;
}

int rmap_init ( RVal * mapval, size_t cap ) {
    if ( !mapval )
        return 0;
    if ( rval_type( mapval ) == RVT_MAP ) {
        if ( !rmap_reserve( mapval, cap / RILL_RMAP_MAXLOD ) )
            return 0;
        rmap_clear( mapval );
        return 1;
    }
    if ( cap < RILL_RMAP_MINSIZ )
        cap = RILL_RMAP_MINSIZ;
    cap += 4 - ( cap % 4 );
    RMap * map = RILL_ALLOC( sizeof( RMap ) + sizeof( RMapSlot ) * cap );
    if ( !map )
        return 0;
    *map = ( RMap ) {
        .occ = 0,
        .cap = cap,
        .ref = 1
    };
    for ( size_t i = 0; i < cap; i++ ) {
        *( map->slt + i ) = ( RMapSlot ) {
            .key = rnil(),
            .val = rnil()
        };
    }
    rmap_release( mapval );
    *mapval = ( RVal ) {
        .typ = RVT_MAP,
        .map = map
    };
    return 1;
}

size_t rmap_size ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    return mapval->map->occ;
}

int rmap_reserve ( RVal * mapval, size_t cap ) {

    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( mapval->map->cap >= cap )
        return 1;
    return rmap_realloc( mapval, cap );
}

int rmap_compact ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    RMap * map = mapval->map;
    size_t target = map->occ / RILL_RMAP_MAXLOD;
    if ( target < RILL_RMAP_MINSIZ / RILL_RMAP_MAXLOD )
        target = RILL_RMAP_MINSIZ / RILL_RMAP_MAXLOD;
    if ( target == map->cap )
        return 1;
    return rmap_realloc( mapval, target );
}

int rmap_clone ( RVal * dst, RVal * src_mapval ) {
    if ( !src_mapval || rval_type( src_mapval ) != RVT_MAP )
        return 0;
    if ( !dst )
        return 0;
    RVal tmp = rnil();
    if ( !rmap_init( &tmp, rmap_size( src_mapval ) ) )
        return 0;
    RMapIter it = rmap_begin( src_mapval );
    while ( it ) {
        // TODO: call rval_clone() here
        if ( !rmap_set( &tmp, rmap_iter_key( it ), rmap_iter_val( it ) ) ) {
            rmap_release( &tmp );
            return 0;
        }

        it = rmap_iter_next( src_mapval, it );
    }
    rval_move( dst, &tmp );
    return 1;
}

int rmap_exclude ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    return rmap_realloc( mapval, mapval->map->occ );
}

int rmap_release ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    RMap * map = mapval->map;
    if ( --map->ref )
        return 1;
    RMapIter it = rmap_begin( mapval );
    while ( it ) {
        rval_release( &it->key );
        rval_release( &it->val );
        it = rmap_iter_next( mapval, it );
    }
    RILL_DEALLOC( map );
    *mapval = rnil();
    return 1;
}

int rmap_set ( RVal * mapval, RVal * keyval, RVal * item ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( !keyval || rval_type( keyval ) != RVT_BUF )
        return 0;

    // if key already exists, just replace its value
    {
        RVal * hit;
        if ( ( hit = rmap_get( mapval, keyval ) ) ) {
            if ( rval_cyclesto( item, mapval ) && !rval_exclude( mapval ) )
                return 0;
            rval_copy( hit, item );
            return 1;
        }
    }

    // resize preemptively
    RMap * map = mapval->map;
    double new_load = ( ( double ) map->occ + 1 ) / ( double ) map->cap;
    if ( new_load > RILL_RMAP_MAXLOD ) {
        if ( !rmap_reserve( mapval, ( double ) map->occ * RILL_RMAP_GROWTH ) )
            return 0;
    }
    map = mapval->map;

    // break cycles
    if ( rval_cyclesto( item, mapval ) && !rval_exclude( mapval ) )
        return 0;
    map = mapval->map;

    // exclude
    if ( map->ref > 1 && !rval_exclude( mapval ) )
        return 0;
    map = mapval->map;

    RMapSlot juggle = ( RMapSlot ) {
        .key = *keyval,
        .val = *item
    };

    rmapslot_swap( &juggle, rmap_hash_a( map, keyval->buf ) );

    while ( 1 ) {
        if ( rval_isnil( &juggle.key ) || rbuf_cmp( &juggle.key, keyval ) == 0 )
            break;
        rmapslot_swap( &juggle, rmap_hash_b( map, juggle.key.buf ) );

        if ( rval_isnil( &juggle.key ) || rbuf_cmp( &juggle.key, keyval ) == 0 )
            break;
        rmapslot_swap( &juggle, rmap_hash_c( map, juggle.key.buf ) );

        if ( rval_isnil( &juggle.key ) || rbuf_cmp( &juggle.key, keyval ) == 0 )
            break;
        rmapslot_swap( &juggle, rmap_hash_d( map, juggle.key.buf ) );

        if ( rval_isnil( &juggle.key ) || rbuf_cmp( &juggle.key, keyval ) == 0 )
            break;
        rmapslot_swap( &juggle, rmap_hash_a( map, juggle.key.buf ) );
    }

    if ( rval_isnil( &juggle.key ) ) {
        rval_lease( keyval );
        rval_lease( item );
        map->occ++;
        return 1;
    } else {
        if ( !rmap_reserve( mapval, map->cap * RILL_RMAP_GROWTH ) )
            return 0;
        return rmap_set( mapval, keyval, item );
    }
}

RVal * rmap_get ( RVal * mapval, RVal * keyval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return NULL;
    if ( !keyval || rval_type( keyval ) != RVT_BUF )
        return NULL;
    RMap * map = mapval->map;
    RBuf * key = keyval->buf;
    RMapSlot * hit;

    hit = rmap_hash_a( map, key );
    if ( !rval_isnil( &hit->key ) && rbuf_cmp( &hit->key, keyval ) == 0 )
        return &hit->val;
    hit = rmap_hash_b( map, key );
    if ( !rval_isnil( &hit->key ) && rbuf_cmp( &hit->key, keyval ) == 0 )
        return &hit->val;
    hit = rmap_hash_c( map, key );
    if ( !rval_isnil( &hit->key ) && rbuf_cmp( &hit->key, keyval ) == 0 )
        return &hit->val;
    hit = rmap_hash_d( map, key );
    if ( !rval_isnil( &hit->key ) && rbuf_cmp( &hit->key, keyval ) == 0 )
        return &hit->val;
    return NULL;
}

RVal * rmap_getc ( RVal * mapval, const char * key ) {
    if ( !key )
        return NULL;
    RVal keyval = rbuf();
    if ( !rbuf_strcpy( &keyval, key ) )
        return NULL;
    RVal * result = rmap_get( mapval, &keyval );
    rval_release( &keyval );
    return result;
}

int rmap_unset ( RVal * mapval, RVal * keyval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( !keyval || rval_type( keyval ) != RVT_BUF )
        return 0;
    RMap * map = mapval->map;
    RBuf * key = keyval->buf;
    RMapSlot * hit;

    hit = rmap_hash_a( map, key );
    if ( !rval_isnil( &hit->key ) && rbuf_cmp( &hit->key, keyval ) == 0 ) {
        rval_release( &hit->key );
        rval_release( &hit->val );
        map->occ--;
        return 1;
    }
    hit = rmap_hash_b( map, key );
    if ( !rval_isnil( &hit->key ) && rbuf_cmp( &hit->key, keyval ) == 0 ) {
        rval_release( &hit->key );
        rval_release( &hit->val );
        map->occ--;
        return 1;
    }
    hit = rmap_hash_c( map, key );
    if ( !rval_isnil( &hit->key ) && rbuf_cmp( &hit->key, keyval ) == 0 ) {
        rval_release( &hit->key );
        rval_release( &hit->val );
        map->occ--;
        return 1;
    }
    hit = rmap_hash_d( map, key );
    if ( !rval_isnil( &hit->key ) && rbuf_cmp( &hit->key, keyval ) == 0 ) {
        rval_release( &hit->key );
        rval_release( &hit->val );
        map->occ--;
        return 1;
    }
    return 0;
}

int rmap_keys ( RVal * dstval, RVal * src_mapval ) {
    if ( !src_mapval || rval_type( src_mapval ) != RVT_MAP )
        return 0;
    if ( !dstval )
        return 0;
    RVal tmp = rnil();
    if ( !rvec_init( &tmp, rmap_size( src_mapval ) ) )
        return 0;
    RMapIter it = rmap_begin( src_mapval );
    while ( it ) {
        if ( !rvec_push( &tmp, rmap_iter_key( it ) ) ) {
            rvec_release( &tmp );
            return 0;
        }
        it = rmap_iter_next( src_mapval, it );
    }
    rval_move( dstval, &tmp );
    return 1;
}

int rmap_vals ( RVal * dstval, RVal * src_mapval ) {
    if ( !src_mapval || rval_type( src_mapval ) != RVT_MAP )
        return 0;
    if ( !dstval )
        return 0;
    RVal tmp = rnil();
    if ( !rvec_init( &tmp, rmap_size( src_mapval ) ) )
        return 0;
    RMapIter it = rmap_begin( src_mapval );
    while ( it ) {
        if ( !rvec_push( &tmp, rmap_iter_val( it ) ) ) {
            rvec_release( &tmp );
            return 0;
        }
        it = rmap_iter_next( src_mapval, it );
    }
    rval_move( dstval, &tmp );
    return 1;
}

int rmap_merge ( RVal * dstval, RVal * srcval ) {
    if ( !dstval || rval_type( dstval ) != RVT_MAP )
        return 0;
    if ( !srcval || rval_type( srcval ) != RVT_MAP )
        return 0;
    // TODO: can you safely rmap_merge without copying?
    RVal tmp = rnil();
    if ( !rmap_init( &tmp, rmap_size( srcval ) ) )
        return 0;
    RMapIter it = rmap_begin( srcval );
    while ( it ) {
        if ( !rmap_set( &tmp, rmap_iter_key( it ), rmap_iter_val( it ) ) ) {
            rval_release( &tmp );
            return 0;
        }
        it = rmap_iter_next( srcval, it );
    }
    rval_move( dstval, &tmp );
    return 1;
}

int rmap_clear ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    RMapIter it = rmap_begin( mapval );
    while ( it ) {
        rmap_iter_del( mapval, it );
        it = rmap_iter_next( mapval, it );
    }
    return 1;
}

RMapIter rmap_begin ( RVal * mapval ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    RMap * map = mapval->map;
    RMapIter it = map->slt;
    if ( !rmap_iter_key( it ) )
        it = rmap_iter_next( mapval, it );
    return it;
}

RMapIter rmap_iter_next ( RVal * mapval, RMapIter it ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( !it )
        return NULL;
    RMap * map = mapval->map;
    RMapSlot * end = map->slt + map->cap;
    it++;
    while ( it < end && rval_isnil( &it->key ) )
        it++;
    if ( it == end )
        it = NULL;
    return it;
}

RVal * rmap_iter_key ( RMapIter it ) {
    if ( !it )
        return NULL;
    if ( rval_isnil( &it->key ) )
        return NULL;
    return &it->key;
}

RVal * rmap_iter_val ( RMapIter it ) {
    if ( !it )
        return NULL;
    if ( rval_isnil( &it->key ) )
        return NULL;
    return &it->val;
}

RMapIter rmap_iter_del ( RVal * mapval, RMapIter it ) {
    if ( !mapval || rval_type( mapval ) != RVT_MAP )
        return 0;
    if ( !it )
        return NULL;
    if ( rval_isnil( &it->key ) )
        return NULL;
    rval_release( &it->key );
    rval_release( &it->val );
    mapval->map->occ--;
    return rmap_iter_next( mapval, it );
}

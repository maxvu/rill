#include "val/rhashmap.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

// TODO: benchmark RHashMap functions' distributions

size_t __hash_a ( RHashMap * map, RRef * keyref ) {
    // http://www.partow.net/programming/hashfunctions/#SDBMHashFunction
    size_t hash = 0;
    uint8_t c;
    const uint8_t * key = rbuf_get( keyref );
    while ( ( c = *key++ ) )
        hash = c + ( hash << 6 ) + ( hash << 16 ) - hash;
    size_t segment_len = map->cap / 4;
    return ( hash % segment_len ) + segment_len * 0;
}

size_t __hash_b ( RHashMap * map, RRef * keyref ) {
    // http://www.partow.net/programming/hashfunctions/#DJBHashFunction
    size_t hash = 5381;
    uint8_t c;
    const uint8_t * key = rbuf_get( keyref );
    while ( ( c = *key++ ) )
        hash = ( hash << 5 ) + hash + c;
    size_t segment_len = map->cap / 4;
    return ( hash % segment_len ) + segment_len * 1;
}

size_t __hash_c ( RHashMap * map, RRef * keyref ) {
    // ...something I made up, twiddling constants from B.
    size_t hash = 56923;
    uint8_t c;
    const uint8_t * key = rbuf_get( keyref );
    while ( ( c = *key++ ) )
        hash = ( hash << 7 ) + hash - c; // 129
    size_t segment_len = map->cap / 4;
    return ( hash % segment_len ) + segment_len * 2;
}

size_t __hash_d ( RHashMap * map, RRef * keyref ) {
    // https://en.wikipedia.org/wiki/Jenkins_hash_function
    size_t hash = 77317;
    uint8_t c;
    const uint8_t * key = rbuf_get( keyref );
    while ( ( c = *key++ ) )
        hash = ( ( hash << 10 ) ^ ( hash >> 6 ) ) + c;
    size_t segment_len = map->cap / 4;
    return ( hash % segment_len ) + segment_len * 3;
}

RHashMap * rhashmap_create ( size_t init_cap ) {
    if ( init_cap < RILL_VAL_RMAP_MINSIZE )
        init_cap = RILL_VAL_RMAP_MINSIZE;
    init_cap += init_cap % 4;
    RHashMap * map = RILL_ALLOC( sizeof( RHashMap ) );
    if ( !map )
        return NULL;
    map->slots = RILL_ALLOC( sizeof( RHashMapSlot ) * init_cap );
    if ( !map->slots ) {
        RILL_DEALLOC( map );
        return NULL;
    }
    for ( size_t i = 0; i < init_cap; i++ ) {
        map->slots->key = rref_nil();
        map->slots->val = rref_nil();
    }
    map->ref = 1;
    map->occ = 0;
    map->cap = init_cap;
    return map;
}

RHashMap * rhashmap_clone ( RHashMap * original ) {
    assert( original );
    RHashMap * clone = rhashmap_create( rhashmap_size( original ) );
    if ( !clone )
        return NULL;
    RHashMapIter it = rhashmap_begin( original );
    while ( it ) {
        RRef * key = rhashmap_iter_key( it );
        RRef * val = rhashmap_iter_val( it );
        if ( !rhashmap_set( clone, key, val ) ) {
            rhashmap_destroy( clone );
            return NULL;
        }
        it = rhashmap_iter_next( original, it );
    }
    return clone;
}

void rhashmap_destroy ( RHashMap * map ) {
    assert( map );
    rhashmap_clear( map );
    RILL_DEALLOC( map->slots );
    RILL_DEALLOC( map );
}

size_t rhashmap_lease ( RHashMap * map ) {
    assert( map );
    return ++map->ref;
}

size_t rhashmap_release ( RHashMap * map ) {
    assert( map );
    return --map->ref;
}

int rhashmap_containsref ( RHashMap * map, RRef * ref ) {
    assert( map );
    RHashMapIter it = rhashmap_begin( map );
    while ( it ) {
        if ( rref_contains( rhashmap_iter_val( it ), ref ) )
            return 1;
        it = rhashmap_iter_next( map, it );
    }
    return 0;
}

size_t rhashmap_size ( RHashMap * map ) {
    assert( map );
    return map->occ;
}

double rhashmap_load ( RHashMap * map ) {
    assert( map );
    return ( double ) map->occ / ( double ) map->cap;
}

int __rhashmap_resize ( RHashMap * map, size_t new_cap ) {
    assert( map );
    RHashMap * resized = rhashmap_create( new_cap );
    if ( !new_cap )
        return 0;
    RHashMapIter it = rhashmap_begin( map );
    while ( it ) {
        RRef * key = rhashmap_iter_key( it );
        RRef * val = rhashmap_iter_val( it );
        if ( !rhashmap_set( resized, key, val ) ) {
            rhashmap_destroy( resized );
            return 0;
        }
        it = rhashmap_iter_next( map, it );
    }

    RHashMap tmp;
    memcpy( &tmp, map, sizeof( RHashMap ) );
    memcpy( map, resized, sizeof( RHashMap ) );

    rhashmap_destroy( &tmp );
    return 1;
}

int rhashmap_reserve ( RHashMap * map, size_t new_cap ) {
    assert( map );
    size_t target = ( double ) new_cap / RILL_VAL_RMAP_MAXLOAD;
    if ( map->cap >= target )
        return 1;
    return __rhashmap_resize( map, target );
}

int rhashmap_compact ( RHashMap * map ) {
    assert( map );
    size_t target = map->occ / RILL_VAL_RMAP_MAXLOAD;
    if ( map->cap == target )
        return 1;
    return __rhashmap_resize( map, target );
}

RRef * rhashmap_get ( RHashMap * map, RRef * key ) {
    assert( map );
    RHashMapSlot * hit;

    hit = map->slots + __hash_a( map, key );
    if ( rbuf_cmp( key, &hit->key ) == 0 ) {
        return &hit->val;
    }

    hit = map->slots + __hash_b( map, key );
    if ( rbuf_cmp( key, &hit->key ) == 0 ) {
        return &hit->val;
    }

    hit = map->slots + __hash_c( map, key );
    if ( rbuf_cmp( key, &hit->key ) == 0 ) {
        return &hit->val;
    }

    hit = map->slots + __hash_d( map, key );
    if ( rbuf_cmp( key, &hit->key ) == 0 ) {
        return &hit->val;
    }

    return NULL;
}

int __slot_occupied ( RHashMapSlot * slot ) {
    return rref_type( &slot->key ) == RRT_BUF;
}

int __try_place_slot ( RHashMap * map, size_t dst_index, RHashMapSlot * src ) {
    RHashMapSlot * dst = map->slots + dst_index;
    if ( !__slot_occupied( dst ) ) {
        rref_copy( &dst->key, &src->key );
        rref_copy( &dst->val, &src->val );
        map->occ++;
        return 1;
    } else if ( rbuf_cmp( &src->key, &dst->key ) == 0 ) {
        rref_copy( &dst->val, &src->val );
        return 1;
    }
    return 0;
}

int rhashmap_set ( RHashMap * map, RRef * key, RRef * val ) {
    assert( map );
    assert( key );

    // If adding another entry would put the table over max-load, resize.
    double new_load = ( double ) ( map->occ + 1 ) / ( double ) map->cap;
    if ( new_load > RILL_VAL_RMAP_MAXLOAD ) {
        size_t target = ( double ) map->occ * RILL_VAL_RMAP_GROWTHCOEFF;
        if ( !rhashmap_reserve( map, target ) )
            return 0;
    }

    // Maintain a yet-to-be-placed slot in "juggle".
    size_t candidate;
    RHashMapSlot juggle;
    rref_copy( &juggle.key, key );
    rref_copy( &juggle.val, val );

    // Try to place in slot A.
    candidate = __hash_a( map, key );
    if ( __try_place_slot( map, candidate, &juggle ) ) {
        rref_release( &juggle.key );
        rref_release( &juggle.val );
        return 1;
    }

    // Evict conflicting value in A and try to place it into B.
    rref_swap( &juggle.key, &map->slots[ candidate ].key );
    rref_swap( &juggle.val, &map->slots[ candidate ].val );
    candidate = __hash_b( map, key );
    if ( __try_place_slot( map, candidate, &juggle ) ) {
        rref_release( &juggle.key );
        rref_release( &juggle.val );
        return 1;
    }

    // Evict conflicting value in B and try to place it into C.
    rref_swap( &juggle.key, &map->slots[ candidate ].key );
    rref_swap( &juggle.val, &map->slots[ candidate ].val );
    candidate = __hash_c( map, key );
    if ( __try_place_slot( map, candidate, &juggle ) ) {
        rref_release( &juggle.key );
        rref_release( &juggle.val );
        return 1;
    }

    // Evict conflicting value in C and try to place it into D.
    rref_swap( &juggle.key, &map->slots[ candidate ].key );
    rref_swap( &juggle.val, &map->slots[ candidate ].val );
    candidate = __hash_d( map, key );
    if ( __try_place_slot( map, candidate, &juggle ) ) {
        rref_release( &juggle.key );
        rref_release( &juggle.val );
        return 1;
    }

    if ( !rhashmap_reserve( map, map->occ * RILL_VAL_RMAP_GROWTHCOEFF ) ) {

        /*
            Very dire situation: can't satisfy the set(), can't resize(),
            can't recover to pre-call state.

            Stash the K/V pair somewhere in this table (where it will most
            likely will not be retrievable with get()) and advise the user that
            the map must be manually recovered via full iterator scan.

            TODO: maybe not this.
        */

        for ( size_t i = 0; i < map->occ; i++ ) {
            if ( !__slot_occupied( map->slots + i ) ) {
                rref_move( &map->slots[ i ].key, &juggle.key );
                rref_move( &map->slots[ i ].key, &juggle.key );
                return 0;
            }
        }
    }

    return rhashmap_set( map, key, val );

}

int rhashmap_unset ( RHashMap * map, RRef * key ) {
    assert( map );
    assert( key );
    RHashMapSlot * hit;

    hit = map->slots + __hash_a( map, key );
    if ( rbuf_cmp( key, &hit->key ) == 0 ) {
        rref_release( &hit->key );
        rref_release( &hit->val );
        map->occ--;
        return 1;
    }

    hit = map->slots + __hash_b( map, key );
    if ( rbuf_cmp( key, &hit->key ) == 0 ) {
        rref_release( &hit->key );
        rref_release( &hit->val );
        map->occ--;
        return 1;
    }

    hit = map->slots + __hash_c( map, key );
    if ( rbuf_cmp( key, &hit->key ) == 0 ) {
        rref_release( &hit->key );
        rref_release( &hit->val );
        map->occ--;
        return 1;
    }

    hit = map->slots + __hash_d( map, key );
    if ( rbuf_cmp( key, &hit->key ) == 0 ) {
        rref_release( &hit->key );
        rref_release( &hit->val );
        map->occ--;
        return 1;
    }

    return 0;

}

void rhashmap_clear ( RHashMap * map ) {
    assert( map );
    RHashMapIter it = rhashmap_begin( map );
    while ( it ) {
        rhashmap_iter_del( map, it );
        it = rhashmap_iter_next( map, it );
    }
}

RHashMapIter rhashmap_begin ( RHashMap * map ) {
    assert( map );
    return map->slots;
}

RHashMapIter rhashmap_iter_next ( RHashMap * map, RHashMapIter iter ) {
    assert( map );
    RHashMapIter begin = map->slots;
    RHashMapIter end = map->slots + map->cap;
    if ( iter < begin || iter >= end )
        return NULL;
    while ( iter < end && !__slot_occupied( iter ) )
        iter++;
    if ( iter == end )
        return NULL;
    return iter;
}

RRef * rhashmap_iter_key ( RHashMapIter iter ) {
    assert( iter );
    return &iter->key;
}

RRef * rhashmap_iter_val ( RHashMapIter iter ) {
    assert( iter );
    return &iter->val;
}

void rhashmap_iter_del ( RHashMap * map, RHashMapIter iter ) {
    assert( iter );
    rref_release( &iter->key );
    rref_release( &iter->val );
    map->occ--;
}

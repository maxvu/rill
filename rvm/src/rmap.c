#include "rerr.h"
#include "rmap.h"
#include "rstr.h"
#include "rval.h"
#include "rvec.h"

#include <stdlib.h>
#include <string.h>

size_t hash_a ( rval * val ) {
    size_t hsh = 0;
    char * pos = rstr_buf( val );
    char * end = pos + rstr_len( val );
    while ( pos < end ) {
        hsh = *pos + ( hsh << 6 ) + ( hsh << 16 ) - hsh;
        ++pos;
    }
    return hsh;
}

size_t hash_b ( rval * val ) {
    size_t hsh = 5381; // djb
    char * pos = rstr_buf( val );
    char * end = pos + rstr_len( val );
    while ( pos < end ) {
        hsh = ( hsh << 5 ) + hsh + *pos;
        ++pos;
    }
    return hsh;
}

size_t hash_c ( rval * val ) {
    size_t hsh = 77317; // one-at-a-time
    char * pos = rstr_buf( val );
    char * end = pos + rstr_len( val );
    while ( pos < end ) {
        hsh = ( ( hsh << 10 ) ^ ( hsh >> 6 ) ) + *pos;
        ++pos;
    }
    return hsh;
}

size_t hash_d ( rval * val ) {
    size_t hsh = 56923; // ???
    char * pos = rstr_buf( val );
    char * end = pos + rstr_len( val );
    while ( pos < end ) {
        hsh = ( hsh << 7 ) ^ ( hsh - *pos );
        ++pos;
    }
    return hsh;
}

rmap_slot * rmap_slot_a ( rval * val, rval * key ) {
    return val->map->slt + (
        hash_a( key ) % val->map->cap
    );
}

rmap_slot * rmap_slot_b ( rval * val, rval * key ) {
    return val->map->slt + (
        hash_b( key ) % val->map->cap + ( val->map->cap / 4 )
    );
}

rmap_slot * rmap_slot_c ( rval * val, rval * key ) {
    return val->map->slt + (
        hash_c( key ) % val->map->cap + ( val->map->cap / 4 ) * 2
    );
}

rmap_slot * rmap_slot_d ( rval * val, rval * key ) {
    return val->map->slt + (
        hash_d( key ) % val->map->cap + ( val->map->cap / 4 ) * 3
    );
}

char rmap_slot_is_hit ( rmap_slot * slot, rval * key ) {
    return rval_type( &slot->key ) != RVT_NIL
        && rstr_cmp( &slot->key, key ) == 0;
}

void rmap_slot_swap ( rmap_slot * a, rmap_slot * b ) {
    rval_swap( &a->key, &b->key );
    rval_swap( &a->val, &b->val );
}

rmap_slot * rmap_find_slot ( rval * val, rval * key ) {
    rmap_slot * slot;
    if ( rmap_slot_is_hit( slot = rmap_slot_a( val, key ), key ) )
        return slot;
    if ( rmap_slot_is_hit( slot = rmap_slot_b( val, key ), key ) )
        return slot;
    if ( rmap_slot_is_hit( slot = rmap_slot_c( val, key ), key ) )
        return slot;
    if ( rmap_slot_is_hit( slot = rmap_slot_d( val, key ), key ) )
        return slot;
    return NULL;
}

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

rerr rmap_resize ( rval * val, size_t new_cap ) {
    rval tmp = rnil();
    if ( !rmap_init( &tmp, new_cap / RMAP_MAX_LOAD ) )
        return RERR_SYS_ALLOC;
    ASSERT_OK( rmap_merge( &tmp, val ) );
    rval_move( val, &tmp );
    return RERR_OK;
}

rerr rmap_reserve ( rval * val, size_t cap ) {
    ASSERT_MAP( val );
    if ( val->map->cap >= cap )
        return RERR_OK;
    return rmap_resize( val, cap );
}

rerr rmap_compact ( rval * val ) {
    ASSERT_MAP( val );
    size_t target = val->map->occ / RMAP_MAX_LOAD;
    if ( target < RMAP_MINIMUM_SIZE / RMAP_MAX_LOAD )
        target = RMAP_MINIMUM_SIZE / RMAP_MAX_LOAD;
    if ( target == val->map->cap )
        return RERR_OK;
    return rmap_resize( val, target );
}

char rmap_has ( rval * val, rval * key ) {
    ASSERT_MAP( val );
    ASSERT_STR( key );
    return ( NULL != rmap_find_slot( val, key ) );
}

rval * rmap_get ( rval * val, rval * key ) {
    if ( !IS_MAP( val ) ) return NULL;
    if ( !IS_STR( key ) ) return NULL;
    rmap_slot * slot = rmap_find_slot( val, key );
    return slot == NULL ? NULL : &slot->val;
}

rerr rmap_set ( rval * val, rval * key, rval * item ) {
    ASSERT_MAP( val );
    ASSERT_STR( key );
    ASSERT_NOT_NULL( item );
    
    {
        rmap_slot * existing = rmap_find_slot( val, key );
        if ( rmap_slot_is_hit( existing, key ) ) {
            if ( val->map->ref > 1 || rval_cyclesto( val, item ) )
                ASSERT_OK( rval_exclude( val ) );
            rval_move( &existing->val, item );
            return RERR_OK;
        }
    }
    
    if ( ( val->map->occ + 1 ) / val->map->cap > RMAP_MAX_LOAD )
        ASSERT_OK( rmap_reserve( val, val->map->occ * RMAP_GROWTH ) );
    if ( val->map->ref > 1 || rval_cyclesto( item, val ) )
        ASSERT_OK( rval_exclude( val ) );
    
    rmap_slot juggle = ( rmap_slot ) { .key = *key, .val = *item };
    rmap_slot_swap( &juggle, rmap_slot_a( val, &juggle.key ) );
    while ( 1 ) {
        if ( rmap_slot_is_hit( &juggle, key ) )
            break;
        rmap_slot_swap( &juggle, rmap_slot_b( val, &juggle.key ) );
        if ( rmap_slot_is_hit( &juggle, key ) )
            break;
        rmap_slot_swap( &juggle, rmap_slot_c( val, &juggle.key ) );
        if ( rmap_slot_is_hit( &juggle, key ) )
            break;
        rmap_slot_swap( &juggle, rmap_slot_d( val, &juggle.key ) );
        if ( rmap_slot_is_hit( &juggle, key ) )
            break;
        rmap_slot_swap( &juggle, rmap_slot_a( val, &juggle.key ) );
    }
    
    if ( rval_type( &juggle.key ) == RVT_NIL ) {
        rval_lease( key );
        rval_lease( item );
        val->map->occ += 1;
        return RERR_OK;
    }
    
    ASSERT_OK( rmap_reserve( val, val->map->cap * RMAP_GROWTH ) );
    return rmap_set( val, key, item );
}

rerr rmap_unset ( rval * val, rval * key ) {
    ASSERT_MAP( val );
    ASSERT_STR( key );
    rmap_slot * slot = rmap_find_slot( val, key );
    if ( slot != NULL ) {
        rval_release( &slot->key );
        rval_release( &slot->val );
        val->map->occ -= 1;
    }
    return RERR_OK;
}

rerr rmap_qget ( rval * val, const char * key );
rerr rmap_qset ( rval * val, const char * key, rval * item );
rerr rmap_qunset ( rval * val, const char * key, rval * item );

rerr rmap_collect ( rval * dst, rval * map, rval * (*get)( rmapit * ) ) {
    ASSERT_MAP( map );
    ASSERT_NOT_NULL( dst );
    rval tmp = rnil();
    ASSERT_OK( rvec_init( &tmp, rmap_size( map ) ) );
    rmapit it = rmap_begin( map );
    rerr err;
    while ( !rmapit_done( &it ) ) {
        if ( RERR_OK != ( err = rvec_push( &tmp, get( &it ) ) ) ) {
            rval_release( &tmp );
            return err;
        }
        rmapit_next( &it );
    }
    rval_move( dst, &tmp );
    return RERR_OK;
}

rerr rmap_keys ( rval * dst, rval * map ) {
    return rmap_collect( dst, map, rmapit_key );
}

rerr rmap_vals ( rval * dst, rval * map ) {
    return rmap_collect( dst, map, rmapit_val );
}

rerr rmap_merge ( rval * dst, rval * src ) {
    ASSERT_MAP( dst );
    ASSERT_MAP( src );
    rval tmp = rnil();
    ASSERT_OK( rmap_init( &tmp, rmap_size( dst ) + rmap_size( src ) ) );
    rmapit it = rmap_begin( dst );
    rerr err;
    while ( !rmapit_done( &it ) ) {
        err = rmap_set( &tmp, rmapit_key( &it ), rmapit_val( &it ) );
        if ( err != RERR_OK ) {
            rval_release( &tmp );
            return err;
        }
        rmapit_next( &it );
    }
    it = rmap_begin( src );
    while ( !rmapit_done( &it ) ) {
        err = rmap_set( &tmp, rmapit_key( &it ), rmapit_val( &it ) );
        if ( err != RERR_OK ) {
            rval_release( &tmp );
            return err;
        }
        rmapit_next( &it );
    }
    rval_move( dst, &tmp );
    return RERR_OK;
}

rerr rmap_clear ( rval * val ) {
    ASSERT_MAP( val );
    rmapit it = rmap_begin( val );
    while ( !rmapit_done( &it ) ) {
        rmapit_del( &it );
        rmapit_next( &it );
    }
    return RERR_OK;
}

rmapit rmap_begin ( rval * val ) {
    rmapit it = ( rmapit ) {
        .pos = val->map->slt,
        .end = val->map->slt + val->map->cap,
        .map = val->map
    };
    if ( IS_NIL( &it.pos->key ) )
        rmapit_next( &it );
    return it;
}

void rmapit_next ( rmapit * it ) {
    if ( !it )
        return;
    while ( IS_NIL( &it->pos->key ) && it->pos < it->end )
        it->pos++;
}

char rmapit_done ( rmapit * it ) {
    if ( !it )
        return 1;
    return it->pos >= it->end;
}
rval * rmapit_key ( rmapit * it ) {
    if ( !it )
        return NULL;
    return &it->pos->key;
}

rval * rmapit_val ( rmapit * it ) {
    if ( !it )
        return NULL;
    return &it->pos->val;
}

rerr rmapit_del ( rmapit * it ) {
    ASSERT_NOT_NULL( it );
    rval_release( &it->pos->key );
    rval_release( &it->pos->val );
    it->map->occ--;
    return RERR_OK;
}
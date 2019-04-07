#include "rval/rbuf.h"
#include "rval/rfxx.h"
#include "rval/rixx.h"
#include "rval/rmap.h"
#include "rval/rval.h"
#include "rval/ruxx.h"
#include "rval/rvec.h"

#include <stdio.h>

void rval_dump ( RVal * val ) {
    if ( !val )
        printf( "(NULL)" );
    switch ( rval_type( val ) ) {
        case RVT_NIL: printf( "(nil)" ); break;
        case RVT_IXX: printf( "ixx(%ld)", val->ixx ); break;
        case RVT_UXX: printf( "uxx(%lu)", val->uxx ); break;
        case RVT_FXX: printf( "ixx(%lf)", val->fxx ); break;
        case RVT_BUF: printf( "buf(%s)",  val->buf->bts ); break;
        case RVT_VEC: {
            printf( "vec( len %lu cap %lu [", val->vec->len, val->vec->cap);
            for ( size_t i = 0; i < rvec_len( val ); i++ ) {
                rval_dump( rvec_get( val, i ) );
                printf( " " );
            }
            printf( "])");
        } break;
        case RVT_MAP: {
            printf( "map( occ %lu cap %lu {", val->map->occ, val->map->cap );
            RMapIter it = rmap_begin( val );
            while ( it ) {
                rval_dump( rmap_iter_key( it ) );
                printf( " " );
                rval_dump( rmap_iter_val( it ) );
                it = rmap_iter_next( val, it );
            }
            for ( size_t i = 0; i < rvec_len( val ); i++ ) {
                rval_dump( rvec_get( val, i ) );
                printf( " " );
            }
            printf( "})");
        } break;
        default: break;
    }
}

void rmapslot_dbgprint ( RMapSlot * slot ) {
    if ( rval_isnil( &slot->key ) ) {
        printf( "(empty)" );
    } else {
        printf( "'%s' ", rbuf_get( &slot->key ) );
    }
}

void rmap_dbgprint ( RVal * map ) {
    if ( !map )
        return;
    printf( "occ %lu cap %lu\n", map->map->occ, map->map->cap );
    for ( size_t i = 0; i < map->map->cap; i++ ) {
        if ( i != 0 && i % ( map->map->cap / 4 ) == 0 )
            printf( "\n" );
        RMapSlot * slot = map->map->slt + i;
        rmapslot_dbgprint( slot );
    }
    printf( "\n" );
}

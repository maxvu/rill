#include "rval/rbuf.h"
#include "rval/rfxx.h"
#include "rval/rixx.h"
#include "rval/rmap.h"
#include "rval/rnil.h"
#include "rval/rval.h"
#include "rval/ruxx.h"
#include "rval/rvec.h"

#include <assert.h>
#include <stdlib.h>

RValTag rval_type ( RVal * val ) {
    return val->info & RILL_RVAL_TAG_TYPEMASK;
}

RValUserTag rval_usertype ( RVal * val ) {
    return val->info & ~RILL_RVAL_TAG_UTYPEMASK >> 4;
}

int rval_usertype_set ( RVal * val, RValUserTag tag ) {
    val->info &= ~RILL_RVAL_TAG_UTYPEMASK >> 4;
    val->info |= ( tag << 4 ) & RILL_RVAL_TAG_UTYPEMASK;
    return 1;
}

int rval_isnil ( RVal * val ) {
    return rval_type( val ) == RVT_NIL;
}

int rval_copy ( RVal * dst, RVal * src ) {
    if ( !dst ) { assert( 0 ); return 0; }
    if ( !src ) { assert( 0 ); return 0; }
    switch ( rval_type( src ) ) {
        case RVT_NIL: rval_release( dst ); break;
        case RVT_IXX: rixx_set( dst, rixx_get( src ) ); break;
        case RVT_UXX: ruxx_set( dst, ruxx_get( src ) ); break;
        case RVT_FXX: rfxx_set( dst, rfxx_get( src ) ); break;
        case RVT_BUF: {
            if ( dst->buf != src->buf ) {
                rval_release( dst );
                dst->buf = src->buf;
                dst->buf->ref++;
            }
        } break;
        case RVT_VEC: {
            if ( dst->vec != src->vec ) {
                rval_release( dst );
                dst->vec = src->vec;
                dst->vec->ref++;
            }
        } break;
        case RVT_MAP: {
            if ( dst->map != src->map ) {
                rval_release( dst );
                dst->map = src->map;
                dst->map->ref++;
            }
        } break;
        default: break;
    }
    return 1;
}

int rval_move ( RVal * dst, RVal * src ) {
    if ( !dst ) { assert( 0 ); return 0; }
    if ( !src ) { assert( 0 ); return 0; }
    rval_copy( dst, src );
    rval_release( src );
    return 1;
}

int rval_clone ( RVal * dst, RVal * src ) {
    if ( !dst ) { assert( 0 ); return 0; }
    if ( !src ) { assert( 0 ); return 0; }
    switch ( rval_type( src ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX: return rval_copy( dst, src ); break;
        case RVT_BUF: {
            if ( dst->buf == src->buf )
                return 1;
            if ( !rbuf_reserve( dst, rbuf_len( src ) ) )
                return 0;
            return rbuf_cat( dst, src );
        } break;
        case RVT_VEC: return rvec_clone( dst, src ); break;
        case RVT_MAP: return rmap_clone( dst, src ); break;
        default: break;
    }
    return 1;
}

int rval_swap ( RVal * a, RVal * b ) {
    if ( !a ) { assert( 0 ); return 0; }
    if ( !b ) { assert( 0 ); return 0; }
    RVal tmp = rnil();
    rval_move( &tmp, b );
    rval_move( b, a );
    rval_move( a, &tmp );
    return 1;
}

int rval_lease ( RVal * val ) {
    switch ( rval_type( val ) ) {
        case RVT_BUF: val->buf->ref++; break;
        case RVT_VEC: val->vec->ref++; break;
        case RVT_MAP: val->map->ref++; break;
        default: break;
    }
    return 1;
}

int rval_release ( RVal * val ) {
    switch ( rval_type( val ) ) {
        case RVT_BUF: {
            if ( !--val->buf->ref )
                RILL_DEALLOC( val->buf );
        } break;
        case RVT_VEC: {
            if ( !--val->vec->ref )
                RILL_DEALLOC( val->vec );
        } break;
        case RVT_MAP: {
            if ( !--val->map->ref )
                RILL_DEALLOC( val->map );
        } break;
        default: break;
    }
    val->info = 0;
    return 1;
}

int rval_containsref ( RVal * haystack, RVal * needle ) {
    if ( !haystack ) { assert( 0 ); return 0; }
    if ( !needle ) { assert( 0 ); return 0; }
    switch ( rval_type( haystack ) ) {
        case RVT_VEC: {
            if ( rval_type( needle ) == RVT_VEC ) {
                if ( haystack->vec == needle->vec )
                    return 1;
            }
            for ( size_t i = 0; i < rvec_len( haystack ); i++ )
                if ( rval_containsref( rvec_get( haystack, i ), needle ) )
                    return 1;
            return 0;
        } break;
        case RVT_MAP: {
            if ( rval_type( needle ) == RVT_MAP ) {
                if ( haystack->map == needle->map )
                    return 1;
            }
            RMapIter it = rmap_begin( needle );
            while ( it ) {
                RVal * val = rmap_iter_val( it );
                if ( rval_containsref( val, needle ) )
                    return 1;
                it = rmap_iter_next( needle, it );
            }
            return 1;
        } break;
        default: return 0; break;
    }
}

int rval_subsume ( RVal * dst, RVal * src, RVal * container ) { // TODO
    if ( rval_containsref( src, container ) ) {
        RVal tmp = rnil();
        if ( !rval_clone( &tmp, container ) )
            return 0;
        rval_move( container, &tmp );
    }
    rval_copy( dst, src );
    return 1;
}

int rval_eq ( RVal * a, RVal * b ) { // TODO
    if ( !a ) { assert( 0 ); return 0; }
    if ( !b ) { assert( 0 ); return 0; }
    if ( rval_type( a ) != rval_type( b ) )
        return 0;
    switch ( rval_type( a ) ) {
        case RVT_NIL: return 1; break;
        case RVT_IXX: return rixx_get( a ) == rixx_get( b ); break;
        case RVT_UXX: return ruxx_get( a ) == rixx_get( b ); break;
        case RVT_FXX: return rfxx_get( a ) == rixx_get( b ); break;
        case RVT_BUF: return rbuf_cmp( a, b ) == 0; break;
        case RVT_VEC: {
            if ( rvec_len( a ) != rvec_len( b ) )
                return 0;
            for ( size_t i = 0; i < rvec_len( a ); i++ )
                if ( !rval_eq( rvec_get( a, i ), rvec_get( b, i ) ) )
                    return 0;
            return 1;
        } break;
        case RVT_MAP: {
            if ( rmap_size( a ) != rmap_size( b ) )
                return 0;
            RMapIter it = rmap_begin( a );
            while ( it ) {
                RVal * item_a = rmap_iter_val( it );
                RVal * item_b = rmap_get( b, rmap_iter_key( it ) );
                if ( !rval_eq( item_a, item_b ) )
                    return 0;
                it = rmap_iter_next( a, it );
            }
            it = rmap_begin( b );
            while ( it ) {
                RVal * item_a = rmap_get( a, rmap_iter_key( it ) );
                RVal * item_b = rmap_iter_val( it );
                if ( !rval_eq( item_a, item_b ) )
                    return 0;
                it = rmap_iter_next( b, it );
            }
            return 1;
        } break;
        default: return 0; break;
    }
}

void rval_dump ( RVal * val ) { // TODO
    switch ( rval_type( val ) ) {
        case RVT_NIL: break;
        case RVT_IXX: break;
        case RVT_UXX: break;
        case RVT_FXX: break;
        case RVT_BUF: break;
        case RVT_VEC: break;
        case RVT_MAP: break;
    }
}

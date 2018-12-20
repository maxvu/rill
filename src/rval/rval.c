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
            RVal tmp = rbuf( rbuf_len( src ) );
            if ( rval_isnil( &tmp ) )
                return 0;
            if ( !rbuf_cat( &tmp, src ) )
                return 0;
            rval_move( dst, &tmp );
        } break;
        case RVT_VEC: {
            if ( dst->vec == src->vec )
                return 1;
            RVal tmpvec = rvec( rvec_len( src ) );
            if ( rval_isnil( &tmpvec ) )
                return 0;
            RVal tmpitem = rnil();
            for ( size_t i = 0; i < rvec_len( src ); i++ ) {
                if ( !rval_clone( &tmpitem, rvec_get( src, i ) ) ) {
                    rval_release( &tmpvec );
                    rval_release( &tmpitem );
                    return 0;
                }
                rvec_push( &tmpvec, &tmpitem );
            }
            rval_release( &tmpitem );
            rval_move( dst, &tmpvec );
        } break;
        case RVT_MAP: {
            if ( dst->map == src->map )
                return 1;
            RVal tmpmap = rmap( rmap_size( src ) );
            if ( rval_isnil( &tmpmap ) )
                return 0;
            RVal tmpval = rnil();
            RVal tmpkey = rnil();
            RMapIter it = rmap_begin( src );
            while ( it ) {
                int ok = rval_clone( &tmpkey, rmap_iter_key( it ) );
                ok = ok && rval_clone( &tmpkey, rmap_iter_key( it ) );
                ok = ok && rmap_set( &tmpmap, &tmpkey, &tmpval );
                if ( !ok ) {
                    rval_release( &tmpmap );
                    rval_release( &tmpkey );
                    rval_release( &tmpval );
                    return 0;
                }
                it = rmap_iter_next( src, it );
            }
            rval_release( &tmpkey );
            rval_release( &tmpval );
            rval_move( dst, &tmpmap );
        } break;
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

int rval_subsume ( RVal * dst, RVal * src, RVal * container ) { // TODO

}

int rval_eq ( RVal * val ) { // TODO

}

int rval_dump ( RVal * val ) { // TODO

}

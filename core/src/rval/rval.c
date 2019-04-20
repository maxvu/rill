#include "rval/rbuf.h"
#include "rval/rfxx.h"
#include "rval/rixx.h"
#include "rval/rmap.h"
#include "rval/rval.h"
#include "rval/ruxx.h"
#include "rval/rvec.h"

int rval_type ( RVal * val ) {
    if ( !val )
        return 0;
    return val->typ;
}

int rval_lease ( RVal * val ) {
    if ( !val )
        return 0;
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_VDP:
        case RVT_FXX: break;
        case RVT_BUF: val->buf->ref++; break;
        case RVT_VEC: val->vec->ref++; break;
        case RVT_MAP: val->map->ref++; break;
    }
    return 1;
}

int rval_release ( RVal * val ) {
    if ( !val )
        return 0;
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_VDP:
        case RVT_FXX: break;
        case RVT_BUF: rbuf_release( val ); break;
        case RVT_VEC: rvec_release( val ); break;
        case RVT_MAP: rmap_release( val ); break;
    }
    *val = rnil();
    return 1;
}

int rval_exclude ( RVal * val ) {
    if ( !val )
        return 0;
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX:
        case RVT_VDP: return 1; break;
        case RVT_BUF: return rbuf_exclude( val ); break;
        case RVT_VEC: return rvec_exclude( val ); break;
        case RVT_MAP: return rmap_exclude( val ); break;
        default: return 0;
    }
}

int rval_copy ( RVal * dst, RVal * src ) {
    if ( !dst )
        return 0;
    if ( !src )
        return 0;
    switch ( rval_type( src ) ) {
        case RVT_NIL:
            rval_release( dst );
            *dst = rnil();
            break;
        case RVT_IXX:
            rval_release( dst );
            *dst = rixx( src->ixx );
            break;
        case RVT_UXX:
            rval_release( dst );
            *dst = ruxx( src->uxx );
            break;
        case RVT_FXX:
            rval_release( dst );
            *dst = rfxx( src->fxx );
            break;
        case RVT_VDP:
            rval_release( dst );
            *dst = ( RVal ) { .typ = RVT_VDP, .vdp = src->vdp };
        case RVT_BUF:
            rval_release( dst );
            *dst = ( RVal ) { .typ = RVT_BUF, .buf = src->buf };
            dst->buf->ref++;
            break;
        case RVT_VEC:
            rval_release( dst );
            *dst = ( RVal ) { .typ = RVT_VEC, .vec = src->vec };
            dst->vec->ref++;
            break;
        case RVT_MAP:
            rval_release( dst );
            *dst = ( RVal ) { .typ = RVT_MAP, .map = src->map };
            dst->map->ref++;
            break;
        default:
            return 0;
            break;
    }
    return 1;
}

int rval_clone ( RVal * dst, RVal * src ) {
    if ( !dst )
        return 0;
    if ( !src )
        return 0;
    switch ( rval_type( src ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX:
        case RVT_VDP:
            return rval_copy( dst, src );
            break;
        case RVT_BUF: {
            RVal tmp = rnil();
            if ( !rbuf_init( &tmp, rbuf_len( src ) ) )
                return 0;
            if ( !rbuf_cpy( &tmp, src ) )
                return 0;
            rval_release( dst );
            *dst = tmp;
            return 1;
        } break;
        case RVT_VEC:
            return rvec_clone( dst, src );
            break;
        case RVT_MAP:
            return rmap_clone( dst, src );
            break;
        default:
            return 0;
            break;
    }
}

int rval_move ( RVal * dst, RVal * src ) {
    if ( !dst )
        return 0;
    if ( !src )
        return 0;
    rval_copy( dst, src );
    rval_release( src );
    return 1;
}

int rval_swap ( RVal * a, RVal * b ) {
    if ( !a )
        return 0;
    if ( !b )
        return 0;
    RVal tmp = rnil();
    rval_move( &tmp, a );
    rval_move( a, b );
    rval_move( b, &tmp );
    return 1;
}

int rval_eq ( RVal * a, RVal * b ) {
    if ( !a )
        return 0;
    if ( !b )
        return 0;
    if ( rval_type( a ) != rval_type( b ) )
        return 0;
    switch ( rval_type( a ) ) {
        case RVT_NIL: return 1; break;
        case RVT_IXX: return a->ixx == b->ixx; break;
        case RVT_UXX: return a->uxx == b->uxx; break;
        case RVT_FXX: return a->fxx == b->fxx; break;
        case RVT_VDP: return a->vdp == b->vdp; break;
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
                RVal * a_val = rmap_iter_val( it );
                RVal * b_val = rmap_get( b, rmap_iter_key( it ) );
                if ( !rval_eq( a_val, b_val ) )
                    return 0;
                it = rmap_iter_next( a, it );
            }
            return 1;
        } break;
        default: return 0; break;
    }
}

int rval_truthy ( RVal * val ) {
    if ( !val )
        return 0;
    switch ( rval_type( val ) ) {
        case RVT_NIL: return 0; break;
        case RVT_IXX: return val->ixx != 0; break;
        case RVT_UXX: return val->uxx == 0; break;
        case RVT_FXX: return val->fxx != 0.0 && !rfxx_isnan( val ); break;
        case RVT_VDP: return 1; break;
        case RVT_BUF: return rbuf_len( val ) != 0; break;
        case RVT_VEC: return rvec_len( val ) != 0; break;
        case RVT_MAP: return rmap_size( val ) != 0; break;
        default: return 0; break;
    }
}

int rval_isnil ( RVal * val ) {
    if ( !val )
        return 0;
    return val->typ == RVT_NIL;
}

int rval_cyclesto ( RVal * haystack, RVal * needle ) {
    if ( !haystack )
        return 0;
    if ( !needle )
        return 0;
    switch ( rval_type( haystack ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX:
        case RVT_BUF: return 0; break;
        case RVT_VEC: {
            if ( rval_type( needle ) == RVT_VEC )
                if ( haystack->vec == needle->vec )
                    return 1;
            for ( size_t i = 0; i < rvec_len( haystack ); i++ ) {
                if ( rval_cyclesto( rvec_get( haystack, i ), needle ) )
                    return 1;
            }
            return 0;
        } break;
        case RVT_MAP: {
            if ( rval_type( needle ) == RVT_MAP )
                if ( haystack->map == needle->map )
                    return 1;
            RMapIter it = rmap_begin( haystack );
            while ( it ) {
                if ( rval_cyclesto( rmap_iter_val( it ), needle ) )
                    return 1;
                it = rmap_iter_next( haystack, it );
            }
            return 0;
        } break;
        default: return 0; break;
    }
}

RVal rnil () {
    return ( RVal ) {
        .typ = RVT_NIL,
        .uxx = 0
    };
}

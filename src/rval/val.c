#include "rval/val.h"

#include <assert.h>
#include <math.h>

RVal rval_qnil () {
    return ( RVal ) {
        .type = RVT_NIL,
        .uxx  = 0
    };
}

RVal rval_quxx ( RILL_UXX_TYPE u ) {
    return ( RVal ) {
        .type = RVT_UXX,
        .uxx = u
    };
}

RVal rval_qixx ( RILL_IXX_TYPE i ) {
    return ( RVal ) {
        .type = RVT_IXX,
        .ixx = i
    };
}

RVal rval_qfxx ( RILL_FXX_TYPE f ) {
    return ( RVal ) {
        .type = RVT_FXX,
        .fxx = f
    };
}

RVal rval_qbuf ( size_t init_cap ) {
    RVal val = rval_qnil();
    rbuf_init( &val, RILL_RBUF_DEFAULTSIZE );
    return val;
}

RVal rval_qvec ( size_t init_cap ) {
    RVal val = rval_qnil();
    rvec_init( &val, RILL_RVEC_DEFAULTSIZE );
    return val;
}

RVal rval_qmap ( size_t init_cap ) {
    RVal val = rval_qnil();
    rmap_init( &val, RILL_RMAP_DEFAULTSIZE );
    return val;
}

int rval_type ( RVal * val ) {
    assert( val != NULL );
    return val->type;
}

int rval_copy ( RVal * dst, RVal * src ) {
    assert( dst != NULL );
    assert( src != NULL );
    rval_release( dst );
    switch ( src->type ) {
        case RVT_NIL: break;
        case RVT_UXX: ruxx_set( dst, ruxx_get( src ) ); break;
        case RVT_IXX: rixx_set( dst, rixx_get( src ) ); break;
        case RVT_FXX: rfxx_set( dst, rfxx_get( src ) ); break;
        case RVT_BUF:
        case RVT_VEC:
        case RVT_MAP: slab_lease( src->slb ); *dst = *src; break;
        default: return 0;
    }
    return 1;
}

void rval_swap ( RVal * a, RVal * b ) {
    assert( a != NULL );
    assert( b != NULL );
    RVal tmp = *a;
    *a = *b;
    *b = tmp;
}

int rval_clone ( RVal * dst, RVal * src ) {
    assert( dst != NULL );
    assert( src != NULL );
    switch ( src->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: rval_copy( dst, src ); break;
        case RVT_BUF: {
            RVal tmp = rval_qnil();
            if ( !rbuf_clone( &tmp, src ) )
                return 0;
            rval_move( dst, &tmp );
        } break;
        case RVT_VEC: {
            RVal tmp = rval_qnil();
            if ( !rmap_clone( &tmp, src ) )
                return 0;
            rval_move( dst, &tmp );
        } break;
        case RVT_MAP: {
            RVal tmp = rval_qnil();
            if ( !rmap_clone( &tmp, src ) )
                return 0;
            rval_move( dst, &tmp );
        } break;
        default: return 0;
    }
    return 1;
}

void rval_move ( RVal * dst, RVal * src ) {
    assert( dst != NULL );
    assert( src != NULL );
    rval_copy( dst, src );
    rval_release( src );
}

void rval_lease ( RVal * val ) {
    assert( val != NULL );
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: break;
        case RVT_BUF: rbuf_lease( val ); break;
        case RVT_VEC: rvec_lease( val ); break;
        case RVT_MAP: rmap_lease( val ); break;
        default: break;
    }
    return;
}

void rval_release ( RVal * val ) {
    assert( val != NULL );
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: break;
        case RVT_BUF: rbuf_release( val ); break;
        case RVT_VEC: rvec_release( val ); break;
        case RVT_MAP: rmap_release( val ); break;
        default: assert( 0 ); break;
    }
    return;
}

int rval_exclude ( RVal * val ) {
    assert( val != NULL );
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: return 1; break;
        case RVT_BUF:
        case RVT_VEC:
        case RVT_MAP: {
            if ( slab_refcount( val->slb ) == 1 )
                return 1;
            RVal tmp = rval_qnil();
            if ( !rval_clone( &tmp, val ) )
                return 0;
            rval_move( val, &tmp );
        } break;
        default: assert( 0 ); return 0; break;
    }
    return 1;
}

int rval_cycles ( RVal * haystack, RVal * needle ) {
    assert( haystack != NULL );
    assert( needle != NULL );
    if ( !rval_isnatrec( needle ) )
        return 0;
    if ( !rval_isnatrec( haystack ) )
        return 0;
    if ( haystack->slb == needle->slb )
        return 1;
    switch ( rval_type( haystack ) ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX:
        case RVT_BUF: assert( 0 ); return 0; break;
        case RVT_VEC: {
            size_t n = rvec_len( haystack );
            for ( size_t i = 0; i < n; i++ ) {
                if ( rval_cycles( rvec_get( haystack, i ), needle ) )
                    return 1;
            }
        } break;
        case RVT_MAP: {
            RMapIter it = rmap_begin( haystack );
            while ( it ) {
                if ( rval_cycles( rmap_iter_val( it ), needle ) )
                    return 1;
                it = rmap_iter_next( haystack, it );
            }
        } break;
    }
    return 0;
}

int rval_isfw ( RVal * val ) {
    assert( val != NULL );
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: return 1; break;
        default: return 0;
    }
}

int rval_isnil ( RVal * val ) {
    assert( val != NULL );
    return rval_type( val ) == RVT_NIL;
}

int rval_isnatrec ( RVal * val ) {
    assert( val != NULL );
    switch ( rval_type( val ) ) {
        case RVT_VEC:
        case RVT_MAP: return 1; break;
        default: return 0;
    }
}

int rval_istruthy ( RVal * val ) {
    switch ( rval_type( val ) ) {
        case RVT_NIL: return 0;
        case RVT_UXX: return ruxx_get( val ) != 0;
        case RVT_IXX: return rixx_get( val ) != 0;
        case RVT_FXX: return !rfxx_isnan( val ) && rfxx_get( val ) != 0; break;
        case RVT_BUF: rbuf_len( val ); break;
        case RVT_VEC: rvec_len( val ); break;
        case RVT_MAP: rmap_size( val ); break;
        default: assert( 0 ); break;
    }
    return 0;
}

int rval_eq ( RVal * val );
int rval_serialize ( RVal * dstbuf, RVal * val );
void rval_dump ( RVal * val );

void ruxx_set ( RVal * val, RILL_UXX_TYPE u ) {
    rval_release( val );
    *val = ( RVal ) {
        .type = RVT_UXX,
        .uxx = u
    };
}

RILL_UXX_TYPE ruxx_get ( RVal * val ) {
    assert( rval_type( val ) );
    return val->uxx;
}

void rixx_set ( RVal * val, RILL_IXX_TYPE i ) {
    rval_release( val );
    *val = ( RVal ) {
        .type = RVT_IXX,
        .ixx = i
    };
}

RILL_IXX_TYPE rixx_get ( RVal * val ) {
    assert( rval_type( val ) == RVT_IXX );
    return val->ixx;
}


int rfxx_isfinite ( RVal * val ) {
    if ( rval_type( val ) != RVT_FXX )
        return 0;
    return isfinite( val->fxx );
}

int rfxx_isnan ( RVal * val ) {
    if ( rval_type( val ) != RVT_FXX )
        return 0;
    return isnan( val->fxx );
}

int rfxx_isinf ( RVal * val ) {
    if ( rval_type( val ) != RVT_FXX )
        return 0;
    return isinf( val->fxx ) == 1;
}

int rfxx_isninf ( RVal * val ) {
    if ( rval_type( val ) != RVT_FXX )
        return 0;
    return isinf( val->fxx ) == -1;
}

void rfxx_set ( RVal * val, RILL_FXX_TYPE f ) {
    rval_release( val );
    val->type = RVT_FXX;
    val->fxx = f;
}

RILL_FXX_TYPE rfxx_get ( RVal * val ) {
    assert( rval_type( val ) == RVT_FXX );
    return val->fxx;
}


int rbuf_init ( RVal * val, size_t init_cap );
size_t rbuf_len ( RVal * buf );
size_t rbuf_cap ( RVal * buf );
int rbuf_reserve ( size_t new_cap );
int rbuf_compact ( RVal * buf );
int rbuf_clone ( RVal * dst, RVal * src );
int rbuf_cpy ( RVal * dst, RVal * src );
int rbuf_cat ( RVal * dst, RVal * src );
int rbuf_cmp ( RVal * a, RVal * b );
int rbuf_cpyc ( RVal * dst, char * cstr );
int rbuf_catc ( RVal * dst, char * cstr );
int rbuf_cmpc ( RVal * dst, char * cstr );
int rbuf_cpyraw ( RVal * dst, uint8_t * raw, size_t raw_len );
int rbuf_catraw ( RVal * dst, uint8_t * raw, size_t raw_len );
int rbuf_cmpraw ( RVal * dst, uint8_t * raw, size_t raw_len );
int rbuf_substr ( RVal * dst, RVal * src, size_t n );
int rbuf_clear ( RVal * buf );

int rvec_init ( RVal * val, size_t init_cap );
size_t rvec_len ( RVal * vec );
size_t rvec_cap ( RVal * vec );
int rvec_reserve ( RVal * vec, size_t new_cap );
int rvec_compact ( RVal * vec );
int rvec_clone ( RVal * dst, RVal * src );
int rvec_eq ( RVal * a, RVal * b );
RVal * rvec_get ( RVal * vec, size_t index );
int rvec_set ( RVal * vec, size_t index, RVal * item );
int rvec_insert ( RVal * vec, size_t index, RVal * item );
int rvec_push ( RVal * vec, RVal * item );
int rvec_pop ( RVal * vec );
int rvec_fill ( RVal * vec, size_t start_index, RVal * item, size_t n );
int rvec_clear ( RVal * vec );

int rmap_init ( RVal * val, size_t init_cap );
size_t rmap_len ( RVal * map );
double rmap_load ( RVal * map );
int rmap_reserve ( RVal * map, size_t new_cap );
int rmap_compact ( RVal * map );
int rmap_clone ( RVal * dst, RVal * src );
int rmap_eq ( RVal * a, RVal * b );
RVal * rmap_get ( RVal * map, RVal * key );
int rmap_set ( RVal * map, RVal * key, RVal * val );
int rmap_unset ( RVal * map, RVal * key );
void rmap_clear ( RVal * map );
typedef RVal * RMapIter;
RMapIter rmap_begin ( RVal * map );
RMapIter rmap_end ( RVal * map );
RMapIter rmap_iter_next ( RVal * map, RMapIter it );
const RVal * rmap_iter_key ( RMapIter it );
RVal * rmap_iter_val ( RMapIter it );
void rmap_iter_unset ( RVal * map, RMapIter it );

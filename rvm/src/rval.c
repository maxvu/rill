#include "rerr.h"
#include "rmap.h"
#include "rstr.h"
#include "rval.h"
#include "rvec.h"

#include <stdlib.h>

rvtype rval_type ( rval * val ) {
    if ( !val )
        return ~RVT_NIL;
    return val->info & 0b1111;
}

unsigned int rval_subtype ( rval * val ) {
    if ( !val )
        return ~0;
    return val->info >> 4;
}

rerr rval_settype ( rval * val, rvtype type ) {
    ASSERT_NOT_NULL( val );
    type = type & 0b1111;
    val->info |= 0b000;
    val->info &= type;
    return RERR_OK;
}

rerr rval_setsubtype ( rval * val, unsigned int subtype ) {
    ASSERT_NOT_NULL( val );
    val->info = ( subtype << 4 ) | rval_type( val );
    return RERR_OK;
}

rerr rval_lease ( rval * val ) {
    ASSERT_NOT_NULL( val );
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX: break;
        case RVT_STR: val->str->ref++; break;
        case RVT_VEC: val->vec->ref++; break;
        case RVT_MAP: val->map->ref++; break;
        default: return RERR_USE_VALTYPE;
    }
    return RERR_OK;
}

rerr rval_release ( rval * val ) {
    ASSERT_NOT_NULL( val );
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX: return RERR_OK;
        case RVT_STR: {
            if ( !--val->str->ref ) {
                free( val->str->buf );
                free( val->str );
            }
        } break;
        case RVT_VEC: {
            if ( val->vec->ref == 1 ) {
                rvec_clear( val );
                free( val->vec->vls );
                free( val->vec );
            } else {
                val->vec->ref -= 1;
            }
        } break;
        case RVT_MAP: {
            if ( val->map->ref == 1 ) {
                rmap_clear( val );
                free( val->map->slt );
                free( val->map );
            } else {
                val->map->ref -= 1;
            }
        } break;
        default: return RERR_USE_VALTYPE;
    }
    *val = rnil();
    return RERR_OK;
}

rerr rval_exclude ( rval * val ) {
    ASSERT_NOT_NULL( val );
    rval tmp = rnil();
    rerr err;
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX: break;
        case RVT_STR: {
            if ( val->str->ref == 1 )
                return RERR_OK;
            if ( RERR_OK != ( err = rval_clone( &tmp, val ) ) )
                return err;
            rval_move( val, &tmp );
        } break;
        case RVT_VEC: {
            if ( val->vec->ref == 1 )
                return RERR_OK;
            if ( RERR_OK != ( err = rvec_clone( &tmp, val ) ) )
                return err;
            rval_move( val, &tmp );
        } break;
        case RVT_MAP: {
            if ( val->map->ref == 1 )
                return RERR_OK;
            if ( RERR_OK != ( err = rmap_init( &tmp, rmap_size( val ) ) ) )
                return err;
            if ( RERR_OK != ( err = rmap_merge( &tmp, val ) ) )
                return err;
            rval_move( val, &tmp );
        } break;
    }
    return RERR_OK;
}

int rval_cyclesto ( rval * to, rval * from ) {
    if ( !to || !from )
        return 0;
    switch ( rval_type( from ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX:
        case RVT_STR: return 0; break;
        case RVT_VEC: {
            if ( to->vec == from->vec )
                return 1;
            for ( size_t i = 0; i < rvec_len( from ); i++ )
                if ( rval_cyclesto( to, rvec_peek( from, i ) ) )
                    return 1;
            return 0;
        } break;
        case RVT_MAP: {
            if ( to->map == from->map )
                return 1;
            rmapit it = rmap_begin( from );
            while ( !rmapit_done( &it ) ) {
                if ( rval_cyclesto( to, rmapit_val( &it ) ) )
                    return 1;
                rmapit_next( &it );
            }
            return 0;
        } break;
        default: return RERR_USE_VALTYPE;
    }
}

rerr rval_copy ( rval * dst, rval * src ) {
    ASSERT_NOT_NULL( dst );
    ASSERT_NOT_NULL( src );
    if ( dst == src )
        return RERR_OK;
    rval_release( dst );
    *dst = *src;
    rval_lease( dst );
    return RERR_OK;
}

rerr rval_clone ( rval * dst, rval * src ) {
    ASSERT_NOT_NULL( dst );
    ASSERT_NOT_NULL( src );
    rval tmp = rnil();
    rerr err;
    switch ( rval_type( src ) ) {
        case RVT_NIL:
        case RVT_IXX:
        case RVT_UXX:
        case RVT_FXX: return rval_copy( dst, src ); break;
        case RVT_STR: {
            if ( RERR_OK != ( err = rstr_init( &tmp, rstr_len( src ) ) ) )
                return err;
            if ( RERR_OK != ( err = rstr_cpy( &tmp, src ) ) ) {
                rval_release( &tmp );
                return err;
            }
            rval_move( dst, &tmp );
        } break;
        case RVT_VEC: {
            if ( RERR_OK != ( err = rvec_clone( &tmp, src ) ) )
                return err;
            rval_move( dst, &tmp );
        } break;
        case RVT_MAP: {
            if ( RERR_OK != ( err = rmap_init( &tmp, rmap_size( src ) ) ) )
                return err;
            if ( RERR_OK != ( err = rmap_merge( &tmp, src ) ) )
                return err;
            rval_move( dst, &tmp );
        } break;
    }
    return RERR_OK;
}

rerr rval_move ( rval * dst, rval * src ) {
    ASSERT_NOT_NULL( dst );
    ASSERT_NOT_NULL( src );
    rval_release( dst );
    *dst = *src;
    *src = rnil();
    return RERR_OK;
}

rerr rval_swap ( rval * a, rval * b ) {
    ASSERT_NOT_NULL( a );
    ASSERT_NOT_NULL( b );
    rval tmp = rnil();
    rval_move( &tmp, a );
    rval_move( a, b );
    rval_move( b, &tmp );
    return RERR_OK;
}

char rval_eq ( rval * a, rval * b ) {
    if ( !a || !b )
        return 0;
    if ( rval_type( a ) != rval_type( b ) )
        return 0;
    switch ( rval_type( b ) ) {
        case RVT_NIL: return 1; break;
        case RVT_IXX: return a->ixx == b->ixx; break;
        case RVT_UXX: return a->uxx == b->uxx; break;
        case RVT_FXX: return a->fxx == b->fxx; break;
        case RVT_STR: return rstr_cmp( a, b ) == 0; break;
        case RVT_VEC: {
            if ( rvec_len( a ) != rvec_len( b ) )
                return 0;
            for ( size_t i = 0; i < rvec_len( a ); i++ )
                if ( !rval_eq( rvec_peek( a, i ), rvec_peek( b, i ) ) )
                    return 0;
            return 1;
        } break;
        case RVT_MAP: {
            if ( rmap_size( a ) != rmap_size( b ) )
                return 0;
            rmapit it = rmap_begin( a );
            while ( !rmapit_done( &it ) ) {
                rval * av = rmapit_val( &it );
                rval * bv = NULL; // rmap_peek( b, rmapit_key( &it ) );
                if ( !rval_eq( av, bv ) )
                    return 0;
                rmapit_next( &it );
            }
            return 1;
        } break;
    }
}

int rval_truthy ( rval * val ) {
    if ( !val )
        return 0;
    switch ( rval_type( val ) ) {
        case RVT_NIL: return 0; break;
        case RVT_IXX: return val->ixx != 0; break;
        case RVT_UXX: return val->uxx != 0; break;
        case RVT_FXX: return val->fxx != 0.0 && val->fxx != -0.0; break;
        case RVT_STR: return rstr_len( val ) != 0; break;
        case RVT_VEC: return rvec_len( val ) != 0; break;
        case RVT_MAP: return rmap_size( val ) != 0; break;
        default: return 0;
    }
}

rval rnil () {
    return ( rval ) {
        .info = 0
    };
}

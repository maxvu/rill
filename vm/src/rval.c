#include <assert.h>
#include <string.h>

#include "rval.h"
#include "rstr.h"
#include "rvec.h"

void rval_zero ( RVal * val ) {
    assert( val != NULL );
    val->type = NIL;
    val->uxx = 0;
}

enum RValType rval_type ( RVal * val ) {
    assert( val != NULL );
    return val->type;
}
int rval_lease ( RVal * val );

void rval_clear ( RVal * val ) {
    assert( val != NULL );
    switch ( rval_type( val ) ) {
        case NIL:
        case UXX:
        case IXX:
        case DBL:
            rval_zero( val );
            break;
        case STR:
        assert( val->str != NULL );
        if ( !--val->str->refcount )
            rstr_retire( val );
        rval_zero( val );
        return;
        break;
        case VEC:
        assert( val->vec != NULL );
        if ( !--val->vec->refcount )
            rvec_retire( val );
        rval_zero( val );
        return;
        break;
        // TODO: map
    }
}

int rval_compact ( RVal * val );

int __exclude_str ( RVal * str ) {
    assert( str != NULL );
    assert( rval_type( str ) == STR );
    if ( str->str->refcount == 1 )
        return 1;
    RVal tmp;
    if ( !rstr_init( &tmp, rstr_len( str ) ) )
        return 0;
    if ( !rstr_set( &tmp, str ) ) {
        rstr_retire( &tmp );
        return 0;
    }
    rval_clear( str );
    memcpy( str, &tmp, sizeof( RVal ) );
    return 1;
}

int __exclude_vec ( RVal * vec ) {
    assert( vec != NULL );
    assert( rval_type( vec ) == VEC );
    if ( vec->vec->refcount == 1 )
        return 1;
    RVal tmp;
    if ( !rvec_init( &tmp, rvec_len( vec ) ) )
        return 0;
    size_t len = rvec_len( vec );
    for ( size_t i = 0; i < len; i++ ) {
        if ( !rvec_push( &tmp, rvec_get( vec, i ) ) ) {
            rvec_retire( &tmp );
            return 0;
        }
    }
    rval_clear( vec );
    memcpy( vec, &tmp, sizeof( RVal ) );
    return 1;
}

int __exclude_map ( RMap * map ) {
    // TODO: implement
    return 1;
}

int rval_exclude ( RVal * val ) {
    assert( val != NULL );
    switch ( rval_type( val ) ) {
        case NIL:
        case UXX:
        case IXX:
        case DBL:
            return 1;
            break;
        case STR:
            return __exclude_str( val );
            break;
        case VEC:
            return __exclude_vec( val );
        // TODO: vec, map
    }
    return 1;
}

int rval_copy ( RVal * dst, RVal * src ) {
    assert( dst != NULL );
    assert( src != NULL );
    rval_clear( dst );
    switch ( rval_type( src ) ) {
        case NIL:
            dst->type = NIL;
        break;
        case UXX:
            dst->type = UXX;
            dst->uxx = src->uxx;
        break;
        case IXX:
            dst->type = IXX;
            dst->ixx = src->ixx;
        break;
        case DBL:
            dst->type = DBL;
            dst->dbl = src->dbl;
        break;
        case STR:
            dst->type = STR;
            dst->str = src->str;
            dst->str->refcount++;
        break;
        // TODO: vec, map
    }
    return 1;
}

int rval_clone ( RVal * dst, RVal * src );
int rval_descends ( RVal * needle, RVal * haystack );

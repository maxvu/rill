#include <assert.h>
#include <string.h>

#include "rval.h"
#include "rstr.h"

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
        // TODO: map, vec
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
    // TODO: implement
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

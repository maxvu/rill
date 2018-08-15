#include <assert.h>
#include <string.h>

#include "rval.h"
#include "rstr.h"

void rval_zero ( RVal * val );
enum RValType rval_type ( RVal * val ) {
    assert( val != NULL );
    return val->type;
}
int rval_lease ( RVal * val );
void rval_clear ( RVal * val );
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
int rval_copy ( RVal * dst, RVal * src );
int rval_clone ( RVal * dst, RVal * src );
int rval_descends ( RVal * needle, RVal * haystack );

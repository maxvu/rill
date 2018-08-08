#include <assert.h>

#include "val/rval.h"
#include "val/rstr.h"
#include "val/rvec.h"

int rval_retire ( RVal * val ) {
    assert( val != NULL );
    switch ( val->type ) {
        case NIL:
        case UXX:
        case IXX:
        case DBL:
            return 1;
            break;
        case STR:
            rstr_retire( val->str );
            break;
        case VEC:
            rvec_retire( val->vec );
            break;
    }
    val->type = NIL;
    return 1;
}

RValType rval_type ( RVal * val ) {
    assert( val != NULL );
    return val->type;
}

int rval_contains ( RVal * haystack, RVal * needle ) {
    assert( haystack != NULL );
    assert( needle != NULL );
    return 0; // TODO: not this
}

int rval_copy ( RVal * dst, RVal * src ) {
    assert( dst != NULL );
    assert( src != NULL );
    rval_release( dst );
    switch ( src->type ) {
        case NIL: break;
        case UXX:
            dst->uxx = src->uxx;
        break;
        case IXX:
            dst->ixx = src->ixx;
        break;
        case DBL:
            dst->dbl = src->dbl;
        break;
        case STR:
            dst->str = src->str;
            rstr_lease( dst->str );
        break;
        case VEC:
            dst->vec = src->vec;
            rvec_lease( dst->vec );
        break;
    }
    dst->type = src->type;
    return 1;
}

int rval_clone ( RVal * dst, RVal * src ) {
    assert( dst != NULL );
    assert( src != NULL );
    rval_release( dst );
    switch ( src->type ) {
        case NIL:
        case UXX:
        case IXX:
        case DBL:
            return rval_copy( dst, src );
        break;
        case STR:

            if ( !( dst->str = rstr_create( rstr_len( src->str ) ) ) )
                return 0;
            return rstr_set( dst->str, src->str );
        break;
        case VEC:
            return rvec_clone( dst->vec, src->vec );
        break;
    }
}

void rval_lease ( RVal * val ) {
    switch ( val->type ) {
        case NIL:
        case UXX:
        case IXX:
        case DBL:
            return;
        break;
        case STR:
            rstr_lease( val->str );
        break;
        case VEC:
            rvec_lease( val->vec );
        break;
    }
}

void rval_release ( RVal * val ) {
    assert( val != NULL );
    switch ( val->type ) {
        case NIL:
        case UXX:
        case IXX:
        case DBL:
        break;
        case STR:
            rstr_release( val->str );
        break;
        case VEC:
            rvec_release( val->vec );
        break;
    }
    val->type = NIL;
}

int rval_exclude ( RVal * val ) {
    assert( val != NULL );
    switch ( val->type ) {
        case NIL:
        case UXX:
        case IXX:
        case DBL:
            return 1;
        break;
        case STR:
            return rstr_exclude( val->str );
        break;
        case VEC:
            return rvec_exclude( val->vec );
        break;
    }
}

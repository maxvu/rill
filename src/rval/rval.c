#include "rval/rval.h"

void rval_fzero ( RVal * val ) {
    assert( val );
    val->type = RVT_NIL;
    val->uxx = 0;
}

RValType rval_type ( RVal * val ) {
    assert( val );
    return val->type;
}

int rval_copy ( RVal * dst, RVal * src ) {

}

int rval_clone ( RVal * dst, RVal * src ) {

}

int rval_compact ( RVal * val ) {

}

int rval_lease ( RVal * val ) {

}

int rval_zero ( RVal * val ) {

}

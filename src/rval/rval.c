#include <assert.h>

#include "rval/rctx.h"
#include "rval/rval.h"

void rval_fzero ( RVal * val ) {

}

RValType rval_type ( RVal * val ) {
    assert( val != NULL );
    return val->type;
}

int rval_copy ( RCtx * ctx, RVal * dst, RVal * src ) {

}

int rval_clone ( RCtx * ctx, RVal * dst, RVal * src ) {

}

int rval_compact ( RCtx * ctx, RVal * val ) {

}

int rval_lease ( RCtx * ctx, RVal * val ) {

}

int rval_clear ( RCtx * ctx, RVal * val ) {

}

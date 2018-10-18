#include "rval/rctx.h"

RCtx * rctx_create () {
    return ( RCtx * ) malloc( sizeof( RCtx ) );
}

RBuf * rctx_alloc_buf ( size_t init_cap ) {

}

RVec * rctx_alloc_vec ( size_t init_cap ) {

}

RMap * rctx_alloc_map ( size_t init_cap ) {

}

void * rctx_reclaim ( RVal * val ) {

}

void rctx_destroy ( RCtx * ctx ) {

}

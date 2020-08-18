#include "platform.h"
#include "rerr.h"
#include "rval.h"
#include "rval_impl.h"

#include <assert.h>
#include <stddef.h>

UXX    rval_type     ( rval * val, rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( val, 0 );
    return val->hed.typ;
}

rval * rval_clone    ( rval * src, rerr * err ) {
    RILL_PROPAGATE_ERR( NULL );
    RILL_ASSERT_NOT_NULL( src, NULL );
    switch ( rval_type( src, NULL ) ) { // TODO: rval_clone
        case RVT_NUM: break;
        case RVT_STR: break;
        case RVT_VEC: break;
        case RVT_MAP: break;
        case RVT_EXT: break;
        default:
            if ( err ) *err = RERR_TYPE;
            return NULL;

    }
    return NULL;
}

IXX   rval_contains ( rval * hay, rval * ndl, rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( hay, 0 );
    RILL_ASSERT_NOT_NULL( ndl, 0 );
    switch ( rval_type( hay, NULL ) ) { // TODO: rval_contains
        case RVT_NUM: break;
        case RVT_STR: break;
        case RVT_VEC: break;
        case RVT_MAP: break;
        case RVT_EXT: break;
        default:
            if ( err ) *err = RERR_TYPE;
            return 0;
    }
    return 0;
}

rval * rval_ref      ( rval * val, rerr * err ) {
    RILL_PROPAGATE_ERR( NULL );
    RILL_ASSERT_NOT_NULL( val, NULL );
    UXX ref = val->hed.ref;
    UXX inc = ref + 1;
    if ( inc > ref ) {
        val->hed.ref = inc;
        return val;
    }
    rval * cln = rval_clone( val, err );
    if ( rerr_ok( err ) )
        return cln;
    return NULL;
}

void   rval_deref    ( rval * val, rerr * err ) {
    RILL_PROPAGATE_ERR();
    RILL_ASSERT_NOT_NULL( val, );
    UXX ref = val->hed.ref - 1;
    if ( ref == 0 - 1 ) {
        if ( err ) *err = RERR_OVRF;
        return;
    }
    val->hed.ref = ref;
}

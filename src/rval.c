#include "platform.h"
#include "rerr.h"
#include "rval.h"
#include "rnum.h"
#include "rstr.h"
#include "rvec.h"
#include "rmap.h"
#include "rval_impl.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

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

void   rval_deref    ( rval * val ) {
    if ( !val )
        return;
    UXX ref = val->hed.ref - 1;
    UXX typ = val->hed.typ;
    if ( ref == 0 ) {
        switch ( typ ) {
            case RVT_NUM:
            case RVT_STR: free( val ); break;
            // case RVT_VEC: rvec_destroy( val ); break;
            // case RVT_MAP: rmap_destroy( val ); break;
            default: 0; break; /* TODO: deref unenumerated types */
        }
        return;
    }
    val->hed.ref = ref;
}

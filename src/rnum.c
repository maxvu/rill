#include "rval.h"
#include "rval_impl.h"

#include <stdlib.h>
#include <math.h>

rval * rnum_create ( rerr * err ) {
    rnum * num = malloc( sizeof( rnum ) );
    if ( !num ) {
        if ( err ) *err = RERR_MEM;
        return NULL;
    }
    rval_head hed = {
        .typ = RVT_NUM,
        .ref = 1,
        .tag = 0
    };
    num->hed = hed;
    return ( rval * ) num;
}

IXX    rnum_geti   ( rval * num, rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( num, 0 );
    RILL_ASSERT_TYPE( num, RVT_NUM, 0 );
    return ( ( rnum * ) num )->ixx;
}

rval * rnum_seti   ( rval * num, IXX    i,  rerr * err ) {
    RILL_PROPAGATE_ERR( num );
    RILL_ASSERT_NOT_NULL( num, num );
    RILL_ASSERT_TYPE( num, RVT_NUM, num );
    if ( num->hed.ref > 1 ) {
        rval * tmp = rval_clone( num, err );
        if ( !rerr_ok( err ) )
            return num;
        rval_deref( num );
        num = tmp;
    }
    ( ( rnum * ) num )->ixx = i;
    return num;
}

UXX    rnum_getu   ( rval * num, rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( num, 0 );
    RILL_ASSERT_TYPE( num, RVT_NUM, 0 );
    return ( ( rnum * ) num )->uxx;
}

rval * rnum_setu   ( rval * num, UXX    u,  rerr * err ) {
    RILL_PROPAGATE_ERR( num );
    RILL_ASSERT_NOT_NULL( num, num );
    RILL_ASSERT_TYPE( num, RVT_NUM, num );
    if ( num->hed.ref > 1 ) {
        rval * tmp = rval_clone( num, err );
        if ( !rerr_ok( err ) )
            return num;
        rval_deref( num );
        num = tmp;
    }
    ( ( rnum * ) num )->uxx = u;
    return num;
}

FXX    rnum_getf   ( rval * num, rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( num, NAN );
    RILL_ASSERT_TYPE( num, RVT_NUM, NAN );
    return ( ( rnum * ) num )->fxx;
}

rval * rnum_setf   ( rval * num, FXX    f,  rerr * err ) {
    RILL_PROPAGATE_ERR( num );
    RILL_ASSERT_NOT_NULL( num, num );
    RILL_ASSERT_TYPE( num, RVT_NUM, num );
    if ( num->hed.ref > 1 ) {
        rval * tmp = rval_clone( num, err );
        if ( !rerr_ok( err ) )
            return num;
        rval_deref( num );
        num = tmp;
    }
    ( ( rnum * ) num )->fxx = f;
    return num;
}

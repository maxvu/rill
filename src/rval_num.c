#include "rval.h"
#include "rval_impl.h"

#include <stdlib.h>
#include <math.h>

typedef struct rnum {
    rval_head hed;
    union {
        IXX ixx;
        UXX uxx;
        FXX fxx;
    };
} rnum;

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

void   rnum_seti   ( rval * num, IXX    i,  rerr * err ) {
    RILL_PROPAGATE_ERR();
    RILL_ASSERT_NOT_NULL( num, );
    RILL_ASSERT_TYPE( num, RVT_NUM, );
    ( ( rnum * ) num )->ixx = i;
}

UXX    rnum_getu   ( rval * num, rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( num, 0 );
    RILL_ASSERT_TYPE( num, RVT_NUM, 0 );
    return ( ( rnum * ) num )->uxx;
}

void   rnum_setu   ( rval * num, UXX    u,  rerr * err ) {
    RILL_PROPAGATE_ERR();
    RILL_ASSERT_NOT_NULL( num, );
    RILL_ASSERT_TYPE( num, RVT_NUM, );
    ( ( rnum * ) num )->uxx = u;
}

FXX    rnum_getf   ( rval * num, rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( num, NAN );
    RILL_ASSERT_TYPE( num, RVT_NUM, NAN );
    return ( ( rnum * ) num )->fxx;
}

void   rnum_setf   ( rval * num, FXX    f,  rerr * err ) {
    RILL_PROPAGATE_ERR();
    RILL_ASSERT_NOT_NULL( num, );
    RILL_ASSERT_TYPE( num, RVT_NUM, );
    ( ( rnum * ) num )->fxx = f;
}

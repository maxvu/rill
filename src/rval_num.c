#include "rval.h"
#include "rval_impl.h"

#include <stdlib.h>

typedef struct rnum {
    UXX hed;
    union {
        IXX ixx;
        UXX uxx;
        FXX fxx;
    };
} rnum;

rerr rnum_create ( rval ** out ) {
    rval * num = malloc( sizeof( rnum ) );
    if ( !num )
        return RERR_MEM;
    rnum_seti( num, 0 );
    *out = num;
    return RERR_OK;
}

rerr rnum_geti  ( rval * num, IXX * out ) {
    if ( !num || !out ) return
        RERR_NULL;
    UXX typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    *out = ( ( rnum * ) num )->ixx;
    return RERR_OK;
}

rerr rnum_seti  ( rval * num, IXX   i ) {
    if ( !num ) return
        RERR_NULL;
    UXX typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    ( ( rnum * ) num )->ixx = i;
    return RERR_OK;
}

rerr rnum_getu  ( rval * num, UXX * out ) {
    if ( !num || !out ) return
        RERR_NULL;
    UXX typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    *out = ( ( rnum * ) num )->uxx;
    return RERR_OK;
}

rerr rnum_setu  ( rval * num, UXX   u ) {
    if ( !num ) return
        RERR_NULL;
    UXX typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    ( ( rnum * ) num )->uxx = u;
    return RERR_OK;
}

rerr rnum_getf  ( rval * num, FXX * out ) {
    if ( !num || out ) return
        RERR_NULL;
    UXX typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    *out = ( ( rnum * ) num )->fxx;
    return RERR_OK;
}

rerr rnum_setf  ( rval * num, FXX   f ) {
    if ( !num ) return
        RERR_NULL;
    UXX typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    ( ( rnum * ) num )->fxx = f;
    return RERR_OK;
}

#include "rval.h"
#include "rval_impl.h"

typedef struct rnum {
    UXX hed;
    union {
        IXX ixx;
        UXX uxx;
        FXX fxx;
    };
} rnum;

rerr rixx_get  ( rval * num, IXX * out ) {
    if ( !num || !out ) return
        RERR_NULL;
    char typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    *out = ( ( rnum * ) num )->ixx;
    return RERR_OK;
}

rerr rixx_set  ( rval * num, IXX   i ) {
    if ( !num ) return
        RERR_NULL;
    char typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    ( ( rnum * ) num )->ixx = i;
    return RERR_OK;
}

rerr ruxx_get  ( rval * num, UXX * out ) {
    if ( !num || !out ) return
        RERR_NULL;
    char typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    *out = ( ( rnum * ) num )->uxx;
    return RERR_OK;
}

rerr ruxx_set  ( rval * num, UXX   u ) {
    if ( !num ) return
        RERR_NULL;
    char typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    ( ( rnum * ) num )->uxx = u;
    return RERR_OK;
}

rerr rfxx_get  ( rval * num, FXX * out ) {
    if ( !num || out ) return
        RERR_NULL;
    char typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    *out = ( ( rnum * ) num )->fxx;
    return RERR_OK;
}

rerr rfxx_set  ( rval * num, FXX   f ) {
    if ( !num ) return
        RERR_NULL;
    char typ;
    rerr err;
    if ( ( err = rval_type( num, &typ ) ) )
        return err;
    if ( typ > RVT_FXX )
        return RERR_TYPE;
    ( ( rnum * ) num )->fxx = f;
    return RERR_OK;
}

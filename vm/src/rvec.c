#include <assert.h>

#include "rval.h"
#include "rvec.h"

static int __resize ( RVec * vec, size_t new_cap ) {
    assert( vec != NULL );
    assert( new_cap >= RILL_VM_RVEC_MIN_SIZE );
    assert( new_cap >= vec->len );
    RVal * new_vals = malloc( sizeof( RVal ) * new_cap );
    if ( !new_vals )
        return 0;
    for ( size_t i = 0; i < new_cap; i++ ) {
        rval_zero( new_vals + i );
    }
    if ( vec->vals != NULL ) {
        memcpy( new_vals, vec->vals, sizeof( RVal ) * vec->len );
        free( vec->vals );
    }
    vec->vals = new_vals;
    vec->cap = new_cap;
    return 1;
}

int rvec_init ( RVal * val, size_t init_cap ) {
    assert( val != NULL );
    rval_clear( val );
    RVec * vec = ( RVec * ) malloc( sizeof( RVec ) );
    if ( !vec )
        return 0;
    if ( init_cap <= RILL_VM_RVEC_MIN_SIZE )
        init_cap = RILL_VM_RVEC_MIN_SIZE;
    vec->vals = NULL;
    vec->len = 0;
    vec->cap = 0;
    vec->refcount = 1;
    vec->up = NULL;
    if ( !__resize( vec, init_cap ) ) {
        free( vec );
        return 0;
    }
    val->vec = vec;
    val->type = VEC;
    return 1;
}

void rvec_retire ( RVal * val ) {
    assert( val != NULL );
    assert( rval_type( val ) == VEC );
    free( val->vec->vals );
    free( val->vec );
    val->vec = NULL;
    val->type = NIL;
}

int rvec_reserve ( RVal * val, size_t new_cap ) {
    assert( val != NULL );
    asser( rval_type( val ) == VEC );
    RVec * vec = val->vec;
    assert( vec != NULL );
    if ( new_cap <= vec->cap )
        return 1;
    return __resize( vec, new_cap * RILL_VM_RVEC_GROWTHCOEFF );
}

int rvec_compact ( RVal * val ) {
    assert( val != NULL );
    assert( rval_type( val ) == VEC );
    RVec * vec = val->vec;
    assert( vec != NULL );
    if ( vec->len <= RILL_VM_RVEC_MIN_SIZE )
        return __resize( vec, RILL_VM_RVEC_MIN_SIZE );
    return __resize( vec, vec->len );
}

int rvec_copy ( RVal * dst, RVal * src ) {

}

int rvec_clone ( RVal * dst, RVal * src ) {

}

size_t rvec_len ( RVal * val ) {

}

RVal * rvec_get ( RVal * val, size_t index ) {

}

int rvec_set ( RVal * val, size_t index, const RVal * item ) {

}

int rvec_push ( RVal * val, RVal * item ) {

}

void rvec_pop ( RVec * vec ) {

}

void rvec_clear ( RVec * vec ) {

}

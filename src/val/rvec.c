#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "val/rvec.h"
#include "val/rval.h"

/* Implementation-specific */

int __resize ( RVec * vec, size_t new_cap ) {
    assert( vec != NULL );
    assert( new_cap >= RILL_VAL_RVEC_DEFAULTLEN );
    assert( new_cap >= vec->len );
    RVal * new_vals = ( RVal * ) calloc( new_cap, sizeof( RVal ) );
    if ( new_vals == NULL )
        return 0;
    memcpy( new_vals, vec->vals, vec->len );
    free( vec->vals );
    vec->vals = new_vals;
    vec->cap = new_cap;
    return 1;
}

/* Construction, destruction */

int rvec_init ( RVec * vec, size_t init_cap ) {
    assert( vec != NULL );
    if ( init_cap < RILL_VAL_RVEC_DEFAULTLEN )
        init_cap = RILL_VAL_RVEC_DEFAULTLEN;
    RVal * vals = ( RVal * ) calloc( init_cap, sizeof( RVal ) );
    if ( vals == NULL ) {
        return 0;
    }
    vec->len = 0;
    vec->cap = init_cap;
    vec->refcount = 1;
    return 1;
}

void rvec_retire ( RVec * vec ) {
    assert( vec != NULL );
    assert( vec->refcount == 1 );
    free( vec->vals );
}

RVec * rvec_create ( size_t init_cap ) {
    RVec * vec = ( RVec * ) malloc( sizeof( RVec ) );
    if ( vec == NULL )
        return NULL;
    if ( !rvec_init( vec, init_cap ) ) {
        free( vec );
        return 0;
    }
    return vec;
}

void rvec_destroy ( RVec * vec ) {
    assert( vec != NULL );
    rvec_retire( vec );
    free( vec );
}

/* RVal-generic */

int rvec_contains ( RVec * vec, RVal * val ) {
    return 0;
}

int rvec_clone ( RVec * dst, RVec * src ) {
    assert( dst != NULL );
    assert( src != NULL );
    if ( !rvec_reserve( dst, src->len ) )
        return 0;
    rvec_clear( dst );
    if ( src->len )
        memcpy( dst->vals, src->vals, sizeof( RVal ) * src->len );
    for ( size_t i = 0; i < src->len; i++ )
        rval_lease( dst->vals + i );
    dst->len = src->len;
    return 1;
}

int rvec_lease ( RVec * vec ) {
    assert( vec != NULL );
    vec->refcount++;
    return 1;
}

int rvec_release ( RVec * vec ) {
    assert( vec != NULL );
    if ( !--vec->refcount )
        rvec_retire( vec );
    return 1;
}

int rvec_exclude ( RVec * vec ) {

}

/* Length and capacity */

int rvec_reserve ( RVec * vec, size_t new_cap ) {
    assert( vec != NULL );
    if ( new_cap < RILL_VAL_RVEC_DEFAULTLEN )
        new_cap = RILL_VAL_RVEC_DEFAULTLEN;
    if ( new_cap <= vec->cap )
        return 1;
    return __resize( vec, new_cap * RILL_VAL_RVEC_GROWTHCOEF );
}

int rvec_compact ( RVec * vec ) {
    assert( vec != NULL );
    if ( vec->cap <= RILL_VAL_RVEC_DEFAULTLEN )
        return 1;
    return __resize( vec, vec->len );
}

size_t rvec_len ( RVec * vec ) {
    assert( vec != NULL );
    return vec->len;
}

/* Access */

RVal * rvec_get ( RVec * vec, size_t index ) {
    assert( vec != NULL );
    if ( index >= vec->len )
        return NULL;
    return vec->vals + index;
}

int rvec_push ( RVec * vec, RVal * item ) {
    assert( vec != NULL );
    if ( !rvec_reserve( vec, vec->len + 1 ) )
        return 1;
    rval_copy( vec->vals + vec->len++, item );
    return 1;
}

int rvec_pop ( RVec * vec ) {
    assert( vec != NULL );
    if ( !vec->len )
        return 0;
    rval_release( vec->vals + vec->len-- );
    return 1;
}

int rvec_clear ( RVec * vec ) {
    assert( vec != NULL );
    for ( size_t i = 0; i < vec->len; i++ )
        rval_release( vec->vals + i );
    vec->len = 0;
    return 1;
}

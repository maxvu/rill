#include "val/rvector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

RVector * rvector_create ( size_t init_cap ) {
    if ( init_cap < RILL_VAL_RVECTOR_MINSIZE )
        init_cap = RILL_VAL_RVECTOR_MINSIZE;
    RVector * vec = RILL_ALLOC( sizeof( RVector ) );
    if ( !vec )
        return NULL;
    if ( !( vec->vals = RILL_ALLOC( sizeof( RRef ) * init_cap ) ) ) {
        RILL_DEALLOC( vec );
        return NULL;
    }
    for ( size_t i = 0; i < init_cap; i++ )
        vec->vals[ i ] = rref_nil();
    vec->ref = 1;
    vec->len = 0;
    vec->cap = init_cap;
    return vec;
}

RVector * rvector_clone ( RVector * orig ) {
    assert( orig );
    RVector * clone = rvector_create( orig->len );
    if ( !clone )
        return NULL;
    for ( size_t i = 0; i < orig->len; i++ )
        if ( !rvector_push( clone, rvector_get( orig, i ) ) ) {
            rvector_destroy( clone );
            return NULL;
        }
    return clone;
}

void rvector_destroy ( RVector * vec ) {
    assert( vec );
    RILL_DEALLOC( vec->vals );
    RILL_DEALLOC( vec );
}

size_t rvector_lease ( RVector * vec ) {
    assert( vec );
    return ++vec->ref;
}

size_t rvector_release ( RVector * vec ) {
    assert( vec );
    return --vec->ref;
}

int rvector_containsref ( RVector * vec, RRef * ref ) {
    assert( vec );
    for ( size_t i = 0; i < vec->len; i++ )
        if ( rref_contains( vec->vals + i, ref ) )
            return 1;
    return 0;
}

size_t rvector_len ( RVector * vec ) {
    assert( vec );
    return vec->len;
}

int __rvector_resize ( RVector * vec, size_t new_cap ) {
    RRef * new_vals = RILL_REALLOC( vec->vals, new_cap );
    if ( !new_vals )
        return 0;
    vec->vals = new_vals;
    vec->cap = new_cap;
    return 1;
}

int rvector_reserve ( RVector * vec, size_t new_cap ) {
    assert( vec );
    if ( vec->cap >= new_cap )
        return 1;
    return __rvector_resize( vec, new_cap );
}

int rvector_compact ( RVector * vec ) {
    assert( vec );
    size_t target = vec->len;
    if ( target < RILL_VAL_RVECTOR_MINSIZE )
        target = RILL_VAL_RVECTOR_MINSIZE;
    if ( vec->cap <= target )
        return 1;
    return __rvector_resize( vec, target );
}

RRef * rvector_get ( RVector * vec, size_t index ) {
    assert( vec );
    if ( index >= vec->len )
        return NULL;
    return vec->vals + index;
}

int rvector_set ( RVector * vec, size_t index, RRef * val ) {
    assert( vec );
    assert( val );
    if ( index >= vec->len )
        return 0;
    rref_copy( vec->vals + index, val );
    return 1;
}

int rvector_push ( RVector * vec, RRef * val ) {
    assert( vec );
    size_t target_size = ( double ) vec->len * RILL_VAL_RVECTOR_GROWTHCOEFF;
    if ( !rvector_reserve( vec, target_size ) )
        return 0;
    rref_copy( vec->vals + vec->len, val );
    vec->len++;
    return 1;
}

int rvector_pop ( RVector * vec ) {
    assert( vec );
    if ( vec->len == 0 )
        return 0;
    vec->len--;
    rref_release( vec->vals + vec->len );
    return 1;
}

void rvector_clear ( RVector * vec ) {
    assert( vec );
    for ( size_t i = 0; i < vec->len; i++ )
        rref_release( vec->vals + i );
    vec->len = 0;
}

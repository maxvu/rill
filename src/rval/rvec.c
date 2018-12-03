#include "environment.h"
#include "rval/rvec.h"
#include "rval/rref.h"

int __rvec_resize ( RVec * vec, size_t new_cap ) {
    TATTLE_IF( vec == NULL );
    TATTLE_IF( new_cap <= vec->len );
    RRef * new_vals = RILL_REALLOC( vec->vals, new_cap );
    if ( new_vals == NULL )
        return 0;
    free( vec->vals );
    vec->vals = new_vals;
    vec->cap = new_cap;
    return 1;
}

RVec * rvec_create ( size_t init_cap ) {
    if ( init_cap < RILL_RVEC_MINSIZE )
        init_cap = RILL_RVEC_MINSIZE;
    RVec * vec = RILL_ALLOC( sizeof( RVec ) );
    if ( vec == NULL )
        return 0;
    vec->vals = RILL_ALLOC( sizeof( RRef ) * init_cap );
    if ( vec->vals == NULL ) {
        free( vec );
        return 0;
    }
    for ( size_t i = 0; i < init_cap; i++ )
        vec->vals[ i ] = rref_nil();
    vec->len = 0;
    vec->cap = init_cap;
    vec->refcount = 1;
    return vec;
}

void rvec_destroy ( RVec * vec ) {
    TATTLE_IF( vec == NULL );
    free( vec->vals );
    free( vec );
}

void rvec_ref ( RVec * vec ) {
    TATTLE_IF( vec == NULL );
    vec->refcount++;
}

void rvec_deref ( RVec * vec ) {
    TATTLE_IF( vec == NULL );
    if ( !--vec->refcount )
        rvec_destroy( vec );
}

int rvec_unique ( RVec * vec ) {
    TATTLE_IF( vec == NULL );
    return vec->refcount == 1;
}

size_t rvec_len ( RVec * vec ) {
    TATTLE_IF( vec == NULL );
    return vec->len;
}

int rvec_reserve ( RVec * vec, size_t new_cap ) {
    TATTLE_IF( vec == NULL );
    if ( new_cap < RILL_RVEC_MINSIZE )
        new_cap = RILL_RVEC_MINSIZE;
    if ( vec->cap >= new_cap )
        return 1;
    return __rvec_resize( vec, (double) new_cap * RILL_RVEC_GROWTHCOEFF );
}

int rvec_compact ( RVec * vec ) {
    TATTLE_IF( vec == NULL );
    size_t target_size = vec->len;
    if ( target_size < RILL_RVEC_MINSIZE )
        target_size = RILL_RVEC_MINSIZE;
    if ( target_size == vec->cap )
        return 1;
    return __rvec_resize( vec, target_size );
}

RRef * rvec_get ( RVec * vec, size_t index ) {
    TATTLE_IF( vec == NULL );
    TATTLE_IF( vec->vals == NULL );
    if ( index >= vec->len )
        return NULL;
    return vec->vals + index;
}

int rvec_set ( RVec * vec, size_t index, RRef * ref ) {
    TATTLE_IF( vec == NULL );
    TATTLE_IF( vec->vals == NULL );
    if ( index >= vec->len )
        return NULL;
    if ( !rval_copy( vec->vals + index, ref ) )
        return 0;
    rref_lease( ref );
    return 1;
}

int rvec_push ( RVec * vec, RRef * ref ) {
    TATTLE_IF( vec == NULL );
    TATTLE_IF( vec->vals == NULL );
    if ( !rvec_reserve( vec, vec->len + 1 ) )
        return 0;
    vec->len++;
    if ( rvec_set( vec, vec->len, ref ) )
        return 1;
    vec->len--;
    return 0;
}

int rvec_pop ( RVec * vec ) {
    TATTLE_IF( vec == NULL );
    TATTLE_IF( vec->vals == NULL );
    if ( vec->len == 0 )
        return 0;
    rref_release( vec->vals + vec->len - 1 );
    vec->len--;
    return 1;
}

int rvec_concat ( RVec * vec, RVec * other ) {
    TATTLE_IF( vec == NULL );
    TATTLE_IF( other == NULL );
    if ( !rvec_reserve( vec, vec->len + other->len ) )
        return 0;
    vec->len += other->len;
    memcpy( vec->vals + vec->len, other->vals, sizeof( RRef ) * other->len );
    for ( size_t i = 0; i < other->len; i++ )
        rref_lease( other->vals + i );
    return 1;
}

int rvec_fill ( RVec * vec, RRef * val, size_t n ) {
    TATTLE_IF( vec == NULL );
    TATTLE_IF( val == NULL );
    if ( !rvec_reserve( vec, vec->len + n ) )
        return 0;
    vec->len += n;
    for ( size_t i = 0; i < n; i++ )
        rvec_push( vec, val );
    return 1;
}

void rvec_clear ( RVec * vec ) {
    TATTLE_IF( vec == NULL );
    for ( size_t i = 0; i < vec->len; i++ )
        rref_release( vec->vals + i );
    memset( vec->vals, 0, sizeof( RRef ) * vec->len );
    vec->len = 0;
}

#include "rmem.h"
#include "rvec.h"

#include <string.h>

int __rvec_resize ( RVec * vec, size_t new_cap ) {
    if ( !vec )
        return 0;
    void * new_data = rmem_alloc( vec->align * new_cap );
    if ( !new_data )
        return 0;
    memcpy( new_data, vec->data, vec->align * vec->len );
    rmem_free( vec->data );
    vec->data = new_data;
    vec->cap = new_cap;
    return 1;
}

RVec * rvec_create ( size_t init_cap, size_t align ) {
    if ( init_cap < RILL_RVEC_MINSIZE )
        init_cap = RILL_RVEC_MINSIZE;
    if ( !align )
        return NULL;
    RVec * vec = rmem_alloc( sizeof( RVec ) );
    if ( !vec )
        return NULL;
    vec->len = 0;
    vec->cap = init_cap;
    vec->align = align;
    vec->data = rmem_alloc( init_cap * align );
    if ( !vec->data ) {
        rmem_free( vec );
        return NULL;
    }
    return vec;
}

RVec * rvec_clone ( RVec * orig ) {
    if ( !orig )
        return NULL;
    size_t new_cap = orig->len * RILL_RVEC_GROWTHFACTOR;
    RVec * clone = rvec_create( new_cap, orig->align );
    if ( !clone )
        return NULL;
    memcpy( clone->data, orig->data, orig->align * orig->len );
    return orig;
}

int rvec_reserve ( RVec * vec, size_t new_cap ) {
    if ( !vec )
        return 0;
    if ( vec->cap >= new_cap )
        return 1;
    __rvec_resize( vec, new_cap );
    return 1;
}

int rvec_compact ( RVec * vec ) {
    if ( !vec )
        return 0;
    size_t new_size = vec->len;
    if ( new_size <= RILL_RVEC_MINSIZE )
        new_size = RILL_RVEC_MINSIZE;
    __rvec_resize( vec, new_size );
    return 1;
}

int rvec_push ( RVec * vec, void * item ) {
    if ( !vec )
        return 0;
    if ( vec->len == vec->cap )
        if ( !rvec_reserve( vec, vec->len * RILL_RVEC_GROWTHFACTOR ) )
            return 1;
    memcpy(
        vec->data + vec->align * vec->len,
        item,
        vec->align
    );
    vec->len++;
    return 1;
}

void * rvec_get ( RVec * vec, size_t index ) {
    if ( !vec )
        return NULL;
    if ( index >= vec->len )
        return NULL;
    return vec->data + index * vec->align;
}

int rvec_set ( RVec * vec, size_t index, void * item ) {
    if ( !vec )
        return 0;
    if ( index >= vec->len )
        return 0;
    memcpy(
        vec->data + vec->align * index,
        item,
        vec->align
    );
    return 1;
}

void rvec_pop ( RVec * vec ) {
    if ( vec && vec->len )
        vec->len--;
}

void rvec_clear ( RVec * vec ) {
    if ( vec )
        vec->len = 0;
    rvec_compact( vec );
}

int rvec_concat ( RVec * vec, const RVec * other ) {
    if ( !vec || !other )
        return 0;
    rvec_reserve( vec, vec->len + other->len );
    memcpy(
        vec->data + vec->align * vec->len,
        other->data,
        other->align * other->len
    );
    vec->len += other->len;
    return 1;
}

size_t rvec_len ( RVec * vec ) {
    if ( !vec )
        return 0;
    return vec->len;
}

size_t rvec_cap ( RVec * vec ) {
    if ( !vec )
        return 0;
    return vec->cap;
}

int rvec_is_empty ( RVec * vec ) {
    return !( vec && vec->len );
}

void rvec_destroy ( RVec * vec ) {
    if ( vec ) {
        rmem_free( vec->data );
        rmem_free( vec );
    }
}

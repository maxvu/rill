#include "rvec.h"

int __rvec_resize ( RVec * vec, size_t new_cap ) {
    if ( !vec || !vec->align || !new_cap ) return 0;
    char * new_buf = rmem_alloc( vec->align * new_cap );
    if ( !new_buf ) return 0;
    memcpy( new_buf, vec->buf, vec->align * vec->len );
    rmem_free( vec->buf );
    vec->buf = new_buf;
    vec->cap = new_cap;
    return 1;
}

RVec * rvec_create ( size_t align ) {
    if ( !align ) return NULL;
    RVec * vec = rmem_alloc( sizeof( RVec ) );
    if ( !vec ) return NULL;
    if ( !rvec_init( vec, align, RILL_RVEC_DEFAULTSIZE ) ) {
        rmem_free( vec );
        return NULL;
    }
    return vec;
}

int rvec_init ( RVec * vec, size_t align, size_t cap ) {
    if ( !vec ) return 0;
    vec->len = 0;
    vec->cap = cap;
    vec->align = align;
    vec->buf = rmem_alloc( align * cap );
    if ( !vec->buf ) return 0;
    return 1;
}

RVec * rvec_clone ( RVec * orig ) {
    if ( !orig ) return NULL;
    RVec * clone = rvec_create( orig->align );
    if ( !clone ) return NULL;
    if ( !rvec_reserve( clone, orig->len ) ) {
        rvec_destroy( clone );
        return NULL;
    }
    memcpy( clone->buf, orig->buf, orig->len * orig->align );
    clone->len = orig->len;
    return clone;
}

size_t rvec_len ( RVec * vec ) {
    if ( !vec ) return 0;
    return vec->len;
}

int rvec_reserve ( RVec * vec, size_t new_cap ) {
    if ( !vec ) return 0;
    if ( new_cap <= vec->cap ) return 1;
    return __rvec_resize( vec, RILL_RVEC_GROWTHFACTOR * new_cap );
}

int rvec_compact ( RVec * vec ) {
    if ( !vec ) return 0;
    if ( vec->cap - vec->len < 2 ) return 1;
    return __rvec_resize( vec, vec->len );
}

void * rvec_get ( RVec * vec, size_t index ) {
    if ( !vec ) return NULL;
    if ( index >= vec->len ) return NULL;
    return vec->buf + index * vec->align ;
}

int rvec_set ( RVec * vec, size_t index, void * item ) {
    if ( !vec ) return 0;
    if ( index == vec->len ) return rvec_push( vec, item );
    if ( index > vec->len ) return 0;
    memcpy( vec->buf + index * vec->align, item, vec->align );
    return 1;
}

void * rvec_head ( RVec * vec ) {
    if ( !vec ) return NULL;
    if ( !vec->len ) return NULL;
    return vec->buf;
}

void * rvec_tail ( RVec * vec ) {
    if ( !vec ) return NULL;
    return rvec_get( vec, vec->len - 1 );
}

int rvec_push ( RVec * vec, void * item ) {
    if ( !vec ) return 0;
    if ( !rvec_reserve( vec, vec->len + 1 ) ) return 0;
    memcpy( vec->buf + vec->len * vec->align , item, vec->align );
    vec->len++;
    return 1;
}

void rvec_pop ( RVec * vec ) {
    if ( !vec || !vec->len ) return;
    vec->len--;
}

void rvec_clear ( RVec * vec ) {
    if ( !vec ) return;
    vec->len = 0;
}

void rvec_retire ( RVec * vec ) {
    if ( !vec ) return;
    rmem_free( vec->buf );
}

void rvec_destroy ( RVec * vec ) {
    if ( !vec ) return;
    rvec_retire( vec );
    rmem_free( vec );
}

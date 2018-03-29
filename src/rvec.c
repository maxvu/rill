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
    vec->len = 0;
    vec->cap = RILL_RVEC_DEFAULTSIZE;
    vec->align = align;
    vec->buf = rmem_alloc( align * vec->cap );
    if ( !vec->buf ) {
        rmem_free( vec );
        return NULL;
    }
    return vec;
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

void rvec_destroy ( RVec * vec ) {
    if ( !vec ) return;
    rmem_free( vec->buf );
    rmem_free( vec );
}

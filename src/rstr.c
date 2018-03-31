#include "rmem.h"
#include "rstr.h"

#include <string.h>

int __rstr_resize ( RStr * str, size_t new_cap ) {
    if ( !new_cap ) return 0;
    char * new_buf = rmem_alloc( new_cap + 1 );
    if ( !new_buf ) return 0;
    memcpy( new_buf, str->buf, str->len + 1 );
    rmem_free( str->buf );
    str->buf = new_buf;
    str->cap = new_cap;
    return 1;
}

int __rstr_set ( RStr * str, const char * other, size_t other_len ) {
    if ( !other_len ) return 1;
    if ( !rstr_reserve( str, other_len ) ) return 0;
    memcpy( str->buf, other, other_len );
    str->len = other_len;
    str->buf[ str->len ] = 0;
    return 1;
}

int __rstr_cat ( RStr * str, const char * other, size_t other_len ) {
    if ( !other_len ) return 1;
    if ( !rstr_reserve( str, str->len + other_len ) ) return 0;
    memcpy( str->buf + str->len, other, other_len );
    str->len += other_len;
    str->buf[ str->len ] = 0;
    return 1;
}

RStr * rstr_create () {
    RStr * str = rmem_alloc( sizeof( RStr ) );
    if ( !str ) return NULL;
    if ( !rstr_init( str ) ) {
        rmem_free( str );
        return NULL;
    }
    return str;
}

int rstr_init ( RStr * str ) {
    if ( !str ) return NULL;
    str->buf = rmem_alloc( RILL_RSTR_DEFAULTSIZE + 1 );
    if ( !str->buf ) {
        rmem_free( str );
        return NULL;
    }
    str->cap = RILL_RSTR_DEFAULTSIZE;
    str->len = 0;
    str->buf[ 0 ] = 0;
    return 1;
}

RStr * rstr_clone ( RStr * orig ) {
    if ( !orig ) return NULL;
    RStr * clone = rstr_create();
    if ( !clone ) return NULL;
    if ( !rstr_reserve( clone, orig->len ) ) {
        rstr_destroy( clone );
        return NULL;
    }
    rstr_set( clone, orig );
    return clone;
}

size_t rstr_len ( RStr * str ) {
    return str->len;
}

int rstr_reserve ( RStr * str, size_t new_cap ) {
    if ( new_cap <= str->cap ) return 1;
    return __rstr_resize( str, RILL_RSTR_GROWTHFACTOR * new_cap );
}

int rstr_compact ( RStr * str ) {
    return __rstr_resize( str, str->len );
}

int rstr_set ( RStr * dst, RStr * src ) {
    return __rstr_set( dst, src->buf, src->len );
}

int rstr_cat ( RStr * dst, RStr * src ) {
    return __rstr_cat( dst, src->buf, src->len );
}

int rstr_cmp ( RStr * dst, RStr * src ) {
    return strcmp( dst->buf, src->buf );
}

int rstr_set_cstr ( RStr * dst, const char * src ) {
    return __rstr_set( dst, src, strlen( src ) );
}

int rstr_cat_cstr ( RStr * dst, const char * src ) {
    return __rstr_cat( dst, src, strlen( src ) );
}

int rstr_cmp_cstr ( RStr * a, const char * b ) {
    return strcmp( a->buf, b );
}

void rstr_retire ( RStr * str ) {
    if ( !str ) return;
    rmem_free( str->buf );
}

void rstr_destroy ( RStr * str ) {
    rstr_retire( str );
    rmem_free( str );
}

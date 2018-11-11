#include "rval.h"

void rval_fzero ( RVal * val ) {
    assert( val );
    val->type = RVT_NIL;
    val->uxx = 0;
}

RValType rval_type ( RVal * val ) {
    assert( val );
    return val->type;
}

int rval_copy ( RVal * dst, RVal * src ) {

}

int rval_clone ( RVal * dst, RVal * src ) {

}

int rval_compact ( RVal * val ) {

}

int rval_lease ( RVal * val ) {

}

int rval_zero ( RVal * val ) {

}

unsigned long ruxx_get ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_UXX );
    return val->uxx;
}

void ruxx_set ( RVal * val, unsigned long u ) {
    assert( val );
    if ( rval_type( val ) != RVT_UXX )
        rval_zero( val );
    val->type = RVT_UXX;
    val->uxx = u;
}

long rixx_get ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_IXX );
    return val->ixx;
}

void rixx_set ( RVal * val, long i ) {
    assert( val );
    if ( rval_type( val ) != RVT_IXX )
        rval_zero( val );
    val->type = RVT_IXX;
    val->ixx = i;
}

double rfxx_get ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_FXX );
    return val->fxx;
}

void rfxx_set ( RVal * val, double u ) {
    assert( val );
    if ( rval_type( val ) != RVT_FXX )
        rval_zero( val );
    val->type = RVT_FXX;
    val->fxx = u;
}


RStr * __rstr_create ( size_t cap ) {
    RStr * str = malloc( sizeof( RStr ) );
    if ( !str )
        return NULL;
    if ( cap < RILL_VM_RBUF_MINSIZE )
        cap = RILL_VM_RBUF_MINSIZE;
    str->buffer = malloc( sizeof( char ) * cap + 1 );
    if ( !str->buffer ) {
        free( str );
        return NULL;
    }
    str->refcount = 0;
    str->len = 0;
    str->cap = cap;
    return str;
}

int __rstr_resize ( RStr * str, size_t new_cap ) {
    assert( str );
    assert( str->buffer );
    assert( new_cap >= str->len );
    char * new_buffer = malloc( sizeof( char ) * new_cap + 1 );
    if ( !new_buffer )
        return 0;
    memcpy( new_buffer, str->buffer, sizeof( char ) * str->len );
    free( str->buffer );
    str->buffer = new_buffer;
    str->cap = new_cap;
    return 1;
}

int __rstr_reserve ( RStr * str, size_t new_cap ) {
    if ( new_cap <= str->cap )
        return 1;
    if ( new_cap < RILL_VM_RBUF_MINSIZE )
        new_cap = RILL_VM_RBUF_MINSIZE;
    return __rstr_resize( str, (double) new_cap * RILL_VM_RBUF_GROWTHCOEFF );
}

int __rstr_cat ( RStr * str, const char * src, size_t src_len ) {
    assert( str );
    assert( str->buffer );
    assert( src );
    if ( !__rstr_reserve( str, str->len + src_len ) )
        return 0;
    memcpy( str->buffer + str->len, src, src_len );
    str->len += src_len;
    str->buffer[ str->len ] = 0;
    return 1;
}

void __rstr_destroy ( RStr * str ) {
    assert( str );
    assert( str->buffer );
    free( str->buffer );
    free( str );
}

int rstr_init ( RVal * val, size_t init_cap ) {
    if ( rval_type( val ) == RVT_STR )
        return __rstr_resize( val->str, init_cap );
    RStr * str = __rstr_create( init_cap );
    if ( !str )
        return 0;
    rval_zero( val );
    val->type = RVT_STR;
    val->str = str;
    return 1;
}

void rstr_lease ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_STR );
    val->str->refcount++;
}

void rstr_release ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_STR );
    if ( --val->str->refcount )
        __rstr_destroy( val->str );
    val->type = RVT_NIL;
    val->str = NULL;
}

int rstr_reserve ( RVal * val, size_t new_cap ) {
    assert( val );
    assert( rval_type( val ) == RVT_STR );
    assert( val->str );
    return __rstr_reserve( val->str, new_cap );
}

int rstr_compact ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_STR );
    assert( val->str );
    size_t target = rstr_len( val );
    if ( target < RILL_VM_RBUF_MINSIZE )
        target = RILL_VM_RBUF_MINSIZE;
    return __rstr_resize( val->str, target );
}

size_t rstr_len ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_STR );
    assert( val->str );
    return val->str->len;
}

const char * rstr_get ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_STR );
    assert( val->str );
    return val->str->buffer;
}

int rstr_set ( RVal * dst, RVal * src ) {
    assert( dst );
    assert( rval_type( dst ) == RVT_STR );
    assert( dst->str );
    assert( src );
    assert( rval_type( src ) == RVT_STR );
    assert( src->str );
    rstr_clear( dst );
    return __rstr_cat( dst->str, src->str->buffer, src->str->len );
}

int rstr_cat ( RVal * dst, RVal * src ) {
    assert( dst );
    assert( rval_type( dst ) == RVT_STR );
    assert( dst->str );
    assert( src );
    assert( rval_type( src ) == RVT_STR );
    assert( src->str );
    return __rstr_cat( dst->str, src->str->buffer, src->str->len );
}

int rstr_cmp ( RVal * a, RVal * b ) {
    assert( a );
    assert( rval_type( a ) == RVT_STR );
    assert( a->str );
    assert( b );
    assert( rval_type( b ) == RVT_STR );
    assert( b->str );
    if ( a->str->len > b->str->len )
        return 1;
    else if ( a->str->len < b->str->len )
        return -1;
    return memcmp( a->str->buffer, b->str->buffer, a->str->len );
}

void rstr_clear ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_STR );
    assert( val->str );
    memset( val->str->buffer, 0, val->str->cap + 1 );
}

int rstr_setc ( RVal * dst, const char * src, size_t src_len ) {
    assert( dst );
    assert( rval_type( dst ) == RVT_STR );
    assert( dst->str );
    assert( src );
    rstr_clear( dst );
    return __rstr_cat( dst->str, src, src_len );
}

int rstr_catc ( RVal * dst, const char * src, size_t src_len ) {
    assert( dst );
    assert( rval_type( dst ) == RVT_STR );
    assert( dst->str );
    assert( src );
    return __rstr_cat( dst->str, src, src_len );
}

int rstr_cmpc ( RVal * a, const char * b, size_t b_len ) {
    assert( a );
    assert( rval_type( a ) == RVT_STR );
    assert( a->str );
    assert( b );
    if ( b_len > a->str->len )
        return -1;
    else if ( b_len > a->str->len )
        return 1;
    return memcmp( a->str->buffer, b, a->str->len );
}

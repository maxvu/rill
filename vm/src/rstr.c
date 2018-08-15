#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "rstr.h"
#include "rval.h"

int __resize ( RStr * str, size_t new_cap ) {
    assert( str != NULL );
    assert( new_cap >= RILL_VM_RSTR_MINSIZE );
    assert( new_cap >= str->len );
    char * new_buf = malloc( sizeof( char ) * new_cap + 1 );
    if ( !new_buf )
        return 0;
    new_buf[ str->len ] = 0;
    if ( str->buf != NULL ) {
        free( str->buf );
        memcpy( new_buf, str->buf, str->len );
    }
    str->buf = new_buf;
    str->cap = new_cap;
    return 1;
}

int __cat ( RStr * str, const char * cstr, size_t cstr_len ) {
    assert( str != NULL );
    assert( cstr != NULL );
    assert( str->len + cstr_len >= str->cap );
    if ( !cstr_len )
        return 1;
    memcpy( str->buf + str->len, cstr, cstr_len );
    str->buf[ str->len ] = 0;
    str->len += cstr_len;
    return 1;
}

int rstr_init ( RVal * val, size_t init_cap ) {
    assert( val != NULL );
    assert( rval_type( val ) == NIL );
    RStr * str = ( RStr * ) malloc( sizeof( RStr ) );
    if ( !str )
        return 0;
    if ( init_cap < RILL_VM_RSTR_MINSIZE )
        init_cap = RILL_VM_RSTR_MINSIZE;
    str->buf = NULL;
    str->len = 0;
    if ( !__resize( str, init_cap ) ) {
        free( str );
        return 0;
    }
    str->refcount = 1;
    val->str = str;
    val->type = STR;
    return 1;
}

void rstr_retire ( RVal * val ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    free( val->str->buf );
    free( val->str );
    val->str = NULL;
    val->type = NIL;
}

int rstr_reserve ( RVal * val, size_t new_cap ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    RStr * str = val->str;
    assert( str != NULL );
    if ( new_cap <= str->cap )
        return 1;
    return __resize( str, new_cap );
}

int rstr_compact ( RVal * val ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    RStr * str = val->str;
    assert( str != NULL );
    if ( str->len <= RILL_VM_RSTR_MINSIZE )
        return __resize( str, RILL_VM_RSTR_MINSIZE );
    return __resize( str, str->len );
}

size_t rstr_len ( RVal * val ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    return val->str->len;
}

const char * rstr_cstr ( RVal * val ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    return val->str->buf;
}

int rstr_set ( RVal * val, RVal * other ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    assert( val->str != NULL );
    assert( other != NULL );
    assert( rval_type( other ) == STR );
    assert( other->str != NULL );
    if ( !rstr_reserve( val, rstr_len( other ) ) )
        return 0;
    val->str->len = 0;
    return __cat( val->str, rstr_cstr( other ), rstr_len( other ) );
}

int rstr_cat ( RVal * val, RVal * other ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    assert( val->str != NULL );
    assert( other != NULL );
    assert( rval_type( other ) == STR );
    assert( other->str != NULL );
    if ( !rstr_reserve( val, rstr_len( other ) ) )
        return 0;
    if ( !rval_exclude( val ) )
        return 0;
    return __cat( val->str, rstr_cstr( other ), rstr_len( other ) );
}

int rstr_cmp ( RVal * val, RVal * other ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    assert( val->str != NULL );
    assert( other != NULL );
    assert( rval_type( other ) == STR );
    assert( other->str != NULL );
    size_t a = rstr_len( val );
    size_t b = rstr_len( other );
    if ( a < b )
        return 1;
    else if ( b > a )
        return -1;
    return memcmp( rstr_cstr( val ), rstr_cstr( other ), a );
}

int rstr_setc ( RVal * val, const char * cstr ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    assert( val->str != NULL );
    assert( cstr != NULL );
    size_t cstr_len = strlen( cstr );
    if ( !rstr_reserve( val, rstr_len( val ) + cstr_len ) )
        return 0;
    if ( !rval_exclude( val ) )
        return 0;
    val->str->len = 0;
    return __cat( val->str, cstr, cstr_len );
}

int rstr_catc ( RVal * val, const char * cstr ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    assert( val->str != NULL );
    assert( cstr != NULL );
    size_t cstr_len = strlen( cstr );
    if ( cstr_len == 0 )
        return 1;
    if ( !rstr_reserve( val, rstr_len( val ) + cstr_len ) )
        return 0;
    if ( !rval_exclude( val ) )
        return 0;
    return __cat( val->str, cstr, cstr_len );
}

int rstr_cmpc ( RVal * val, const char * cstr ) {
    return memcmp( val->str->buf, cstr, val->str->len );
}

void rstr_clear ( RVal * val ) {
    assert( val != NULL );
    assert( rval_type( val ) == STR );
    assert( val->str != NULL );
    val->str->len = 0;
    val->str->buf[ 0 ] = 0;
}

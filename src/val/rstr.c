#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "val/rstr.h"

/* Implementation-specific */

int __cat ( RStr * str, const char * sfx, size_t sfx_len ) {
    assert( str != NULL );
    assert( sfx != NULL );
    if ( sfx_len == 0 )
        return 1;
    if ( !rstr_exclude( str ) )
        return 0;
    if ( !rstr_reserve( str, str->len + sfx_len ) )
        return 0;
    memcpy( str->buf + str->len, sfx, sfx_len );
    str->len += sfx_len;
    str->buf[ str->len ] = 0;
    return 1;
}

int __resize ( RStr * str, size_t new_cap ) {
    assert( str != NULL );
    assert( new_cap >= RILL_VAL_RSTR_DEFAULTLEN );
    assert( new_cap >= str->len );
    char * new_buf = ( char * ) calloc( new_cap + 1, sizeof( char ) );
    if ( !new_buf )
        return 0;
    if ( new_cap > str->cap ) {
        memcpy( new_buf, str->buf, sizeof( char ) * str->cap );
    } else {
        memcpy( new_buf, str->buf, sizeof( char ) * new_cap );
    }
    free( str->buf );
    str->buf = new_buf;
    str->cap = new_cap;
    return 1;
}

/* Construction, destruction */

int rstr_init ( RStr * str, size_t init_cap ) {
    assert( str != NULL );
    if ( init_cap < RILL_VAL_RSTR_DEFAULTLEN )
        init_cap = RILL_VAL_RSTR_DEFAULTLEN;
    char * buf = ( char * ) calloc( init_cap + 1, sizeof( char ) );
    if ( !buf )
        return 0;
    str->buf = buf;
    str->len = 0;
    str->cap = init_cap;
    str->refcount = 1;
    return 1;
}

void rstr_retire ( RStr * str ) {
    assert( str != NULL );
    assert( str->buf != NULL );
    assert( str->refcount == 1 );
    free( str->buf );
    str->buf = NULL;
    str->len = 0;
    str->cap = 0;
}

RStr * rstr_create ( size_t init_cap ) {
    RStr * str = ( RStr * ) malloc( sizeof( RStr ) );
    if ( str == NULL ) {
        return NULL;
    }
    if ( !rstr_init( str, init_cap ) ) {
        free( str );
        return NULL;
    }
    return str;
}

void rstr_destroy ( RStr * str ) {
    assert( str != NULL );
    rstr_retire( str );
    free( str );
}

/* RVal-generic */

int rstr_lease ( RStr * str ) {
    assert( str != NULL );
    str->refcount++;
    return 1;
}

int rstr_release ( RStr * str ) {
    assert( str != NULL );
    assert( str->refcount != 0 );
    str->refcount--;
    if ( --str->refcount == 0 )
        rstr_retire( str );
    return 1;
}

int rstr_exclude ( RStr * str ) {
    assert( str != NULL );
    if ( str->refcount == 1 )
        return 1;
    RStr tmp;
    if ( !rstr_init( &tmp, str->len ) )
        return 0;
    rstr_set( &tmp, str );
    rstr_release( str );
    memcpy( str, &tmp, sizeof( RStr ) );
    return 1;
}

/* Length and capacity */

int rstr_reserve ( RStr * str, size_t new_cap ) {
    assert( str != NULL );
    if ( new_cap < RILL_VAL_RSTR_DEFAULTLEN )
        new_cap = RILL_VAL_RSTR_DEFAULTLEN;
    if ( new_cap <= str->cap )
        return 1;
    return __resize( str, new_cap );
}

int rstr_compact ( RStr * str ) {
    assert( str != NULL );
    if ( str->len <= RILL_VAL_RSTR_GROWTHCOEF )
        return 1;
    return __resize( str, str->len );
}

size_t rstr_len ( RStr * str ) {
    return str->len;
}

/* Raw access */

const char * rstr_cstr ( RStr * str ) {
    assert( str != NULL );
    return str->buf;
}

/* Access */

int rstr_set ( RStr * str, const RStr * other ) {
    assert( str != NULL );
    assert( other != NULL );
    if ( str == other )
        return 1;
    if ( !rstr_setc( str, "" ) )
        return 0;
    return __cat( str, other->buf, other->len );
}

int rstr_cat ( RStr * str, const RStr * other ) {
    assert( str != NULL );
    assert( other != NULL );
    return __cat( str, other->buf, other->len );
}

int rstr_cmp ( RStr * str, const RStr * other ) {
    assert( str != NULL );
    assert( other != NULL );
    if ( str == other )
        return 0;
    if ( str->len > other->len ) {
        return 1;
    } else if ( other->len > str->len ) {
        return -1;
    } else {
        return memcmp( str->buf, other->buf, other->len );
    }
}


/* C-string access */

int rstr_setc ( RStr * str, const char * cstr ) {
    assert( str != NULL );
    assert( cstr != NULL );
    size_t cstr_len = strlen( cstr );
    if ( cstr_len == 0 )
        return 1;
    str->len = 0;
    return __cat( str, cstr, cstr_len );
}

int rstr_catc ( RStr * str, const char * cstr ) {
    assert( str != NULL );
    assert( cstr != NULL );
    size_t cstr_len = strlen( cstr );
    if ( cstr_len == 0 )
        return 1;
    return __cat( str, cstr, cstr_len );
}

int rstr_cmpc ( RStr * str, const char * cstr ) {
    assert( str != NULL );
    assert( cstr != NULL );
    size_t cstr_len = strlen( cstr );
    if ( str->len > cstr_len ) {
        return 1;
    } else if ( cstr_len > str->len ) {
        return -1;
    } else {
        return memcmp( str->buf, cstr, str->len );
    }
}

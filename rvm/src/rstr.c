#include "rerr.h"
#include "rstr.h"
#include "rval.h"

#include <stdlib.h>
#include <string.h>

typedef unsigned int rerr;

rval rstrq ( const char * cstr ) {
    rval tmp = rnil();
    if ( !cstr )
        return tmp;
    size_t cstr_len = strlen( cstr );
    if ( RERR_OK != rstr_init( &tmp, cstr_len ) )
        return tmp;
    if ( RERR_OK != rstr_mcpy( &tmp, ( uint8_t * ) cstr, cstr_len ) )
        rval_release( &tmp );
    return tmp;
}

rerr rstr_init ( rval * val, size_t cap ) {
    ASSERT_NOT_NULL( val );
    if ( IS_STR( val ) )
        return rstr_reserve( val, cap );
    if ( cap < RSTR_MINIMUM_SIZE )
        cap = RSTR_MINIMUM_SIZE;
    char * buf = ( char * ) malloc( sizeof( char ) * cap + 1 );
    if ( !buf )
        return RERR_SYS_ALLOC;
    rstr * str = ( rstr * ) malloc( sizeof( rstr ) );
    if ( !str ) {
        free( buf );
        return RERR_SYS_ALLOC;
    }
    buf[ 0 ] = 0;
    *str = ( rstr ) {
        .ref = 1,
        .buf = buf,
        .len = 0,
        .cap = cap
    };
    *val = ( rval ) {
        .info = RVT_STR,
        .str  = str
    };
    return RERR_OK;
}

size_t rstr_len ( rval * val ) {
    if ( !val || !IS_STR( val ) )
        return 0;
    return val->str->len;
}
char * rstr_buf ( rval * val ) {
    if ( !val || !IS_STR( val ) )
        return NULL;
    return val->str->buf;
}

rerr rstr_resize ( rval * val, size_t new_cap ) {
    char * new_buf = ( char * ) malloc( sizeof( char ) * new_cap + 1 );
    if ( !new_buf )
        return RERR_SYS_ALLOC;
    rstr * str = val->str;
    memcpy( new_buf, str->buf, str->len );
    new_buf[ str->len ] = '\0';
    free( str->buf );
    str->buf = new_buf;
    str->cap = new_cap;
    return RERR_OK;
}

rerr rstr_reserve ( rval * val, size_t new_len ) {
    ASSERT_STR( val );
    if ( new_len <= val->str->cap )
        return RERR_OK;
    return rstr_resize( val, new_len * RSTR_GROWTH );
}

rerr rstr_compact ( rval * val ) {
    ASSERT_STR( val );
    size_t target = val->str->len;
    if ( target <= RSTR_MINIMUM_SIZE )
        target = RSTR_MINIMUM_SIZE;
    return rstr_resize( val, target );
}

rerr rstr_cpy ( rval * dst, rval * src ) {
    ASSERT_STR( dst );
    ASSERT_STR( src );
    ASSERT_OK( rval_exclude( dst ) );
    ASSERT_OK( rstr_reserve( dst, dst->str->len + src->str->len ) );
    return rstr_mcpy( dst, ( uint8_t * ) src->str->buf, src->str->len );
}

rerr rstr_cat ( rval * dst, rval * src ) {
    ASSERT_STR( dst );
    ASSERT_STR( src );
    ASSERT_OK( rval_exclude( dst ) );
    ASSERT_OK( rstr_reserve( dst, dst->str->len + src->str->len ) );
    return rstr_mcat( dst, ( uint8_t * ) src->str->buf, src->str->len );
}

int rstr_cmp ( rval * a, rval * b ) {
    ASSERT_STR( a );
    ASSERT_STR( b );
    return rstr_mcmp( a, ( uint8_t * ) b->str->buf, b->str->len );
}

rerr rstr_mcpy ( rval * val, uint8_t * mem, size_t mem_len ) {
    ASSERT_STR( val );
    ASSERT_NOT_NULL( mem );
    if ( !mem_len ) {
        rstr_clear( val );
        return RERR_OK;
    }
    ASSERT_OK( rval_exclude( val ) );
    ASSERT_OK( rstr_reserve( val, mem_len ) );
    rstr * str = val->str;
    memcpy( str->buf, mem, mem_len );
    str->len = mem_len;
    str->buf[ str->len ] = 0;
    return RERR_OK;
}

rerr rstr_mcat ( rval * val, uint8_t * mem, size_t mem_len ) {
    ASSERT_STR( val );
    ASSERT_NOT_NULL( mem );
    if ( !mem_len )
        return RERR_OK;
    rstr * str = val->str;
    ASSERT_OK( rval_exclude( val ) );
    ASSERT_OK( rstr_reserve( val, str->len + mem_len ) );
    str = val->str; // reserve() and exclude() may change this
    memcpy( str->buf + str->len, mem, mem_len );
    str->len += mem_len;
    str->buf[ str->len ] = '\0';
    return RERR_OK;
}

int rstr_mcmp ( rval * val, uint8_t * mem, size_t mem_len ) {
    ASSERT_STR( val );
    if ( !val || !mem )
        return -1;
    if ( val->str->len && !mem_len )
        return 1;
    else if ( !val->str->len && mem_len )
        return -1;
    else
        return memcmp( rstr_buf( val ), mem, mem_len );
}

rerr rstr_qcpy ( rval * val, const char * cstr ) {
    ASSERT_STR( val );
    ASSERT_NOT_NULL( cstr );
    return rstr_mcpy( val, ( uint8_t * ) cstr, strlen( cstr ) );
}

rerr rstr_qcat ( rval * val, const char * cstr ) {
    ASSERT_STR( val );
    ASSERT_NOT_NULL( cstr );
    return rstr_mcat( val, ( uint8_t * ) cstr, strlen( cstr ) );
}

int rstr_qcmp ( rval * val, const char * cstr ) {
    if ( !IS_STR( val ) || !cstr )
        return -7;
    size_t cstr_len = strlen( cstr );
    return rstr_mcmp( val, ( uint8_t * ) cstr, cstr_len );
}

rerr rstr_clear ( rval * val ) {
    ASSERT_STR( val );
    ASSERT_OK( rval_exclude( val ) );
    val->str->buf[ 0 ] = '\0';
    val->str->len = 0;
    return RERR_OK;
}

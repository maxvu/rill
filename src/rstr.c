#include "rval.h"
#include "rstr.h"
#include "rval_impl.h"

#include <stdlib.h>
#include <string.h>

#define RILL_STRVAL_MIN_SIZE      24
#define RILL_STRVAL_GROWTH_RATE   2.0
#define RILL_STRVAL_SHRINK_BUFFER 8

rval * rstr_create  ( UXX    cap, rerr * err ) {
    RILL_PROPAGATE_ERR( NULL );
    cap = cap < RILL_STRVAL_MIN_SIZE ? RILL_STRVAL_MIN_SIZE : cap;
    cap = cap + ( 8 - cap % 8 ); // round up to the nearest word boundary
    rstr * str = malloc( sizeof( rstr ) + cap );
    if ( !str ) {
        if ( err ) *err = RERR_MEM;
        return NULL;
    }
    str->hed.typ = RVT_STR;
    str->hed.ref = 1;
    str->hed.tag = 0;
    str->len = 0;
    str->cap = cap;
    *( str->buf ) = '\0';
    return ( rval * ) str;
}

UXX    rstr_len     ( rval * str, rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( str, 0 );
    return ( ( rstr * ) str )->len;
}

rval * rstr_reserve ( rval * str, UXX    cap, rerr * err ) {
    RILL_PROPAGATE_ERR( str );
    RILL_ASSERT_NOT_NULL( str, str );
    RILL_ASSERT_TYPE( str, RVT_STR, str );
    if ( cap <= ( ( rstr * ) str )->cap )
        return str;
    rval * dst = rstr_create( cap, err );
    if ( !rerr_ok( err ) )
        return str;
    rstr_cpy( dst, str, NULL );
    rval_deref( str );
    return dst;
}

rval * rstr_compact ( rval * str, rerr * err ) {
    RILL_PROPAGATE_ERR( str );
    RILL_ASSERT_NOT_NULL( str, str );
    RILL_ASSERT_TYPE( str, RVT_STR, str );

    rstr * src = ( rstr * ) str;
    if ( src->cap - src->len < RILL_STRVAL_SHRINK_BUFFER )
        return str;
    UXX target_size = src->len > RILL_STRVAL_MIN_SIZE
        ? src->len
        : RILL_STRVAL_MIN_SIZE;
    rval * dst = rstr_create( target_size, err );
    if ( !rerr_ok( err ) )
        return str;
    rstr_cpy( dst, str, NULL );
    rval_deref( str );
    return dst;
}

rval * rstr_cpy     ( rval * dst, rval * src, rerr * err ) {
    RILL_PROPAGATE_ERR( dst );
    RILL_ASSERT_NOT_NULL( dst, dst );
    RILL_ASSERT_NOT_NULL( src, dst );
    RILL_ASSERT_TYPE( dst, RVT_STR, dst );
    RILL_ASSERT_TYPE( src, RVT_STR, dst );
    dst = rstr_reserve( dst, rstr_len( src, NULL ), err );
    if ( !rerr_ok( err ) )
        return dst;
    memcpy(
        ( ( rstr * ) dst )->buf,
        ( ( rstr * ) src )->buf,
        rstr_len( src, NULL ) + 1
    );
    ( ( rstr * ) dst )->len = rstr_len( src, NULL );
    return dst;
}

rval * rstr_cat     ( rval * dst, rval * src, rerr * err ) {
    RILL_PROPAGATE_ERR( dst );
    RILL_ASSERT_NOT_NULL( dst, dst );
    RILL_ASSERT_NOT_NULL( src, dst );
    RILL_ASSERT_TYPE( dst, RVT_STR, dst );
    RILL_ASSERT_TYPE( src, RVT_STR, dst );
    dst = rstr_reserve(
        dst,
        rstr_len( src, NULL ) * RILL_STRVAL_GROWTH_RATE,
        err
    );
    if ( !rerr_ok( err ) )
        return dst;
    memcpy(
        ( ( rstr * ) dst )->buf + rstr_len( dst, NULL ),
        ( ( rstr * ) src )->buf,
        rstr_len( src, NULL ) + 1
    );
    ( ( rstr * ) dst )->len += rstr_len( src, NULL );
    return dst;
}

int    rstr_cmp     ( rval * a,   rval * b,   rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( a, 0 );
    RILL_ASSERT_NOT_NULL( b, 0 );
    RILL_ASSERT_TYPE( a, RVT_STR, 0 );
    RILL_ASSERT_TYPE( b, RVT_STR, 0 );
    UXX a_len = rstr_len( a, NULL );
    UXX b_len = rstr_len( b, NULL );
    if ( a_len < b_len )
        return -1;
    if ( b_len < a_len )
        return 1;
    return memcmp(
        ( ( rstr * ) a )->buf,
        ( ( rstr * ) b )->buf,
        a_len
    );
}

rval * rstr_cpyc    ( rval * str, const char * src, rerr * err ) {
    RILL_PROPAGATE_ERR( str );
    RILL_ASSERT_NOT_NULL( str, str );
    RILL_ASSERT_TYPE( str, RVT_STR, str );
    if ( !src )
        return str;
    UXX src_len = strlen( src );
    str = rstr_reserve( str, src_len, err );
    if ( !rerr_ok( err ) )
        return str;
    memcpy( ( ( rstr * ) str )->buf, src, src_len + 1 );
    ( ( rstr * ) str )->len = src_len;
    return str;
}

rval * rstr_catc    ( rval * str, const char * src, rerr * err ) {
    RILL_PROPAGATE_ERR( str );
    RILL_ASSERT_NOT_NULL( str, str );
    RILL_ASSERT_TYPE( str, RVT_STR, str );
    if ( !src )
        return str;
    UXX src_len = strlen( src );
    if ( src_len + rstr_len( str, NULL ) < src_len ) {
        if ( err ) *err = RERR_OVRF;
        return str;
    }
    str = rstr_reserve( str, src_len * RILL_STRVAL_GROWTH_RATE, err );
    if ( !rerr_ok( err ) )
        return str;
    memcpy( ( ( rstr * ) str )->buf + rstr_len( str, NULL ), src, src_len + 1 );
    ( ( rstr * ) str )->len += src_len;
    return str;
}

int   rstr_cmpc    ( rval * a,   const char * b,   rerr * err ) {
    RILL_PROPAGATE_ERR( 0 );
    RILL_ASSERT_NOT_NULL( a, 0 );
    RILL_ASSERT_TYPE( a, RVT_STR, 0 );
    if ( !b ) {
        if ( err ) *err = RERR_NULL;
        return 0;
    }
    UXX a_len = rstr_len( a, NULL );
    UXX b_len = strlen( b );
    if ( a_len < b_len )
        return -1;
    if ( b_len < a_len )
        return 1;
    return strcmp( ( ( rstr * ) a )->buf, b );
}

rval * rstr_clear   ( rval * str, rerr * err ) {
    RILL_PROPAGATE_ERR( str );
    RILL_ASSERT_NOT_NULL( str, str );
    RILL_ASSERT_TYPE( str, RVT_STR, str );
    ( ( rstr * ) str )->len = 0;
    *( ( rstr * ) str )->buf = '\0';
    return str;
}

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
    assert( dst );
    assert( src );
    if ( dst == src )
        return 1;
    switch ( rval_type( src ) ) {
        case RVT_NIL:
        break;
        case RVT_UXX:
            ruxx_set( dst, ruxx_get( src ) );
        break;
        case RVT_IXX:
            rixx_set( dst, rixx_get( src ) );
        break;
        case RVT_FXX:
            rfxx_set( dst, rfxx_get( src ) );
        break;
        case RVT_STR:
            return rstr_copy( dst, src );
        break;
        case RVT_VEC:
            return rvec_copy( dst, src );
        break;
        case RVT_MAP:
            /* ... */
        break;
    }
    return 1;
}

int rval_clone ( RVal * dst, RVal * src ) {
    assert( dst );
    assert( src );
    if ( dst == src )
        return 1;
    rval_release( dst );
    switch ( rval_type( src ) ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX:
            return rval_copy( dst, src );
        break;
        case RVT_STR:
            if ( !rstr_init( dst, rstr_len( src ) ) )
                return 0;
            return rstr_cat( dst, src );
        break;
        case RVT_VEC:
            /* ... */
        break;
        case RVT_MAP:
            /* ... */
        break;
    }
}

int rval_exclude ( RVal * val ) {
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX:
            return 1;
        break;
        case RVT_STR: {
            if ( val->str->refcount <= 1 )
                return 1;
        } break;
        case RVT_VEC:
            if ( val->vec->refcount <= 1 )
                return 1;
        break;
        case RVT_MAP:
            /* ... */
        break;
    }
    RVal tmp;
    rval_fzero( &tmp );
    if ( !rval_clone( &tmp, val ) )
        return 0;
    if ( !rval_copy( val, &tmp ) )
        return 0;
    return 1;
}

int rval_contains ( RVal * haystack, RVal * needle ) {
    switch ( rval_type( haystack ) ) {
        case RVT_NIL:
            return 0;
        break;
        case RVT_UXX:
            return 0;
        break;
        case RVT_IXX:
            return 0;
        break;
        case RVT_FXX:
            return 0;
        break;
        case RVT_STR:
            return 0;
        break;
        case RVT_VEC: {
            for ( size_t i = 0; i < rvec_len( haystack ); i++ )
                if ( rval_contains( rvec_get( haystack, i ), needle ) )
                    return 1;
            return 0;
        } break;
        case RVT_MAP:
            /* ... */
        break;
    }
}

int rval_compact ( RVal * val ) {
    switch ( rval_type( val ) ) {
        case RVT_NIL: return 1;
        case RVT_UXX: return 1;
        case RVT_IXX: return 1;
        case RVT_FXX: return 1;
        break;
        case RVT_STR:
            return rstr_compact( val );
        break;
        case RVT_VEC:
            return rvec_compact( val );
        break;
        case RVT_MAP:
            /* ... */
        break;
    }
}

int rval_lease ( RVal * val ) {
    switch ( rval_type( val ) ) {
        case RVT_NIL: return 1;
        case RVT_UXX: return 1;
        case RVT_IXX: return 1;
        case RVT_FXX: return 1;
        break;
        case RVT_STR:
            rstr_lease( val );
            return 1;
        break;
        case RVT_VEC:
            rvec_lease( val );
            return 1;
        break;
        case RVT_MAP:
            /* ... */
        break;
    }
}

int rval_release ( RVal * val ) {
    switch ( rval_type( val ) ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX:
        break;
        case RVT_STR:
            rstr_release( val );
        break;
        case RVT_VEC: {
            rvec_release( val );
        } break;
        case RVT_MAP:
            rmap_clear( val );
        break;
    }
    val->type = RVT_NIL;
    val->uxx = 0;
    return 1;
}

void rval_dump ( RVal * val ) {
    switch ( rval_type( val ) ) {
        case RVT_NIL: printf( "RVal(NIL)" ); break;
        case RVT_UXX: printf( "RVal(UXX:%lu)", ruxx_get( val ) ); break;
        case RVT_IXX: printf( "RVal(IXX: %ld)", rixx_get( val ) ); break;
        case RVT_FXX: printf( "RVal(FXX) %lf", rfxx_get( val ) ); break;
        break;
        case RVT_STR:
            printf(
                "RVal(STR, len %lu, ref %lu [%s]) ",
                rstr_len( val ),
                val->str->refcount,
                rstr_get( val )
            );
            break;
        break;
        case RVT_VEC: {
            printf(
                "RVal(VEC, len %lu, ref %lu, cap %lu [ ",
                rvec_len( val ),
                val->vec->refcount,
                val->vec->cap
            );
            for ( size_t i = 0; i < rvec_len( val ); i++ ) {
                rval_dump( rvec_get( val, i ) );
                printf( " " );
            }
            printf( "]" );
        } break;
        case RVT_MAP:
            printf( "RVal(MAP) " );
        break;
    }
}

unsigned long ruxx_get ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_UXX );
    return val->uxx;
}

void ruxx_set ( RVal * val, unsigned long u ) {
    assert( val );
    if ( rval_type( val ) != RVT_UXX )
        rval_release( val );
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
        rval_release( val );
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
        rval_release( val );
    val->type = RVT_FXX;
    val->fxx = u;
}


RStr * __rstr_create ( size_t cap ) {
    RStr * str = ( RStr * ) malloc( sizeof( RStr ) );
    if ( !str )
        return NULL;
    if ( cap < RILL_RSTR_MINSIZE )
        cap = RILL_RSTR_MINSIZE;
    str->buffer = ( char * ) malloc( sizeof( char ) * cap + 1 );
    if ( !str->buffer ) {
        free( str );
        return NULL;
    }
    str->buffer[ 0 ] = NULL;
    str->refcount = 0;
    str->len = 0;
    str->cap = cap;
    return str;
}

int __rstr_resize ( RStr * str, size_t new_cap ) {
    assert( str );
    assert( str->buffer );
    assert( new_cap >= str->len );
    if ( new_cap < RILL_RSTR_MINSIZE )
        new_cap = RILL_RSTR_MINSIZE;
    char * new_buffer = ( char * ) malloc( sizeof( char ) * new_cap + 1 );
    if ( !new_buffer )
        return 0;
    memcpy( new_buffer, str->buffer, sizeof( char ) * str->len + 1 );
    free( str->buffer );
    str->buffer = new_buffer;
    str->cap = new_cap;
    return 1;
}

int __rstr_reserve ( RStr * str, size_t new_cap ) {
    if ( new_cap <= str->cap )
        return 1;
    if ( new_cap < RILL_RSTR_MINSIZE )
        new_cap = RILL_RSTR_MINSIZE;
    return __rstr_resize( str, (double) new_cap * RILL_RSTR_GROWTHCOEFF );
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
        return __rstr_reserve( val->str, init_cap );
    rval_release( val );
    RStr * str = __rstr_create( init_cap );
    if ( !str )
        return 0;
    rval_release( val );
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
    val->uxx = 0;
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
    if ( target < RILL_RSTR_MINSIZE )
        target = RILL_RSTR_MINSIZE;
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

int rstr_copy ( RVal * dst, RVal * src ) {
    assert( dst );
    assert( src );
    assert( rval_type( src ) == RVT_STR );
    assert( src->str );
    rval_release( dst );
    dst->type = RVT_STR;
    dst->str = src->str;
    rstr_lease( dst );
}

int rstr_cat ( RVal * dst, RVal * src ) {
    assert( dst );
    assert( src );
    if ( rval_type( src ) != RVT_STR )
        return 0;
    assert( src->str );
    if ( rval_type( dst ) != RVT_STR )
        return rstr_copy( dst, src );
    if ( !rval_exclude( dst ) )
        return 0;
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

int rstr_clear ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_STR );
    assert( val->str );
    if ( !rval_exclude( val ) )
        return 0;
    val->str->buffer[ 0 ] = NULL;
    val->str->len = 0;
    return 1;
}

int rstr_setc ( RVal * dst, const char * src, size_t src_len ) {
    assert( dst );
    assert( src );
    if ( rval_type( dst ) != RVT_STR && !rstr_init( dst, src_len ) )
        return 0;
    if ( !rstr_clear( dst ) )
        return 0;
    return __rstr_cat( dst->str, src, src_len );
}

int rstr_catc ( RVal * dst, const char * src, size_t src_len ) {
    assert( dst );
    assert( src );
    if ( rval_type( dst ) != RVT_STR ) {
        rval_release( dst );
        if ( !rstr_init( dst, src_len ) )
            return 0;
    }
    if ( !rval_exclude( dst ) )
        return 0;
    return __rstr_cat( dst->str, src, src_len );
}

int rstr_cmpc ( RVal * a, const char * b, size_t b_len ) {
    assert( a );
    assert( b );
    if ( rval_type( a ) != RVT_STR )
        return -32;
    if ( b_len > a->str->len )
        return -1;
    else if ( b_len < a->str->len )
        return 1;
    return memcmp( a->str->buffer, b, a->str->len );
}

RVec * __rvec_create ( size_t cap ) {
    if ( cap < RILL_RVEC_MINSIZE )
        cap = RILL_RVEC_MINSIZE;
    RVec * vec = ( RVec * ) malloc( sizeof( RVec ) );
    if ( !vec )
        return NULL;
    RVal * vals = ( RVal * ) malloc( sizeof( RVal ) * cap );
    if ( !vals ) {
        free( vec );
        return NULL;
    }
    for ( size_t i = 0; i < cap; i++ )
        rval_fzero( vals + i );
    vec->vals = vals;
    vec->refcount = 1;
    vec->len = 0;
    vec->cap = cap;
    return vec;
}

int __rvec_resize ( RVec * vec, size_t new_cap ) {
    assert( vec );
    assert( new_cap >= vec->len );
    if ( new_cap < RILL_RVEC_MINSIZE )
        new_cap = RILL_RVEC_MINSIZE;
    RVal * new_vals = ( RVal * ) malloc( sizeof( RVal ) * new_cap );
    if ( !new_vals )
        return 0;
    memcpy( new_vals, vec->vals, sizeof( RVal ) * vec->len );
    free( vec->vals );
    vec->vals = new_vals;
    vec->cap = new_cap;
    return 1;
}

int __rvec_reserve ( RVec * vec, size_t new_cap ) {
    if ( new_cap <= vec->cap )
        return 1;
    if ( new_cap <= RILL_RVEC_MINSIZE )
        new_cap = RILL_RVEC_MINSIZE;
    return __rvec_resize( vec, (double) new_cap * RILL_RVEC_GROWTHCOEFF );
}

void __rvec_destroy ( RVec * vec ) {
    assert( vec );
    assert( vec->vals );
    for ( size_t i = 0; i < vec->len; i++ )
        rval_release( vec->vals + i );
    free( vec->vals );
    free( vec );
}

int rvec_init ( RVal * val, size_t init_cap ) {
    assert( val );
    if ( rval_type( val ) == RVT_VEC )
        return __rvec_reserve( val->vec, init_cap );
    RVec * vec = __rvec_create( init_cap );
    if ( !vec )
        return 0;
    rval_release( val );
    val->type = RVT_VEC;
    val->vec = vec;
    return 1;
}

void rvec_lease ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_VEC );
    val->vec->refcount++;
}

void rvec_release ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_VEC );
    if ( !--val->vec->refcount )
        __rvec_destroy( val->vec );
}

int rvec_reserve ( RVal * val, size_t new_cap ) {
    assert( val );
    assert( rval_type( val ) == RVT_VEC );
    return __rvec_reserve( val->vec, new_cap );
}

int rvec_compact ( RVal * val ) {
    assert( val );
    if ( rval_type( val ) != RVT_VEC )
        return 0;
    size_t target = rvec_len( val );
    if ( target < RILL_RVEC_MINSIZE )
        target = RILL_RVEC_MINSIZE;
    return __rvec_resize( val->vec, target );
}

int rvec_copy ( RVal * dst, RVal * src ) {
    if ( rval_type( src ) != RVT_VEC )
        return 0;
    rval_release( dst );
    dst->type = RVT_VEC;
    dst->vec = src->vec;
    dst->vec->refcount++;
    return 1;
}

size_t rvec_len ( RVal * val ) {
    assert( val );
    if ( rval_type( val ) != RVT_VEC )
        return 0;
    return val->vec->len;
}

RVal * rvec_get ( RVal * val, size_t index ) {
    assert( val );
    if ( rval_type( val ) != RVT_VEC )
        return NULL;
    if ( index >= rvec_len( val ) )
        return NULL;
    return val->vec->vals + index;
}

int rvec_set ( RVal * val, size_t index, RVal * item ) {
    assert( val );
    assert( item );
    if ( rvec_len( val ) <= index )
        return 0;
    if ( rval_contains( item, val ) && !rval_exclude( item ) ) {
        return 0;
    }
    if ( !rval_exclude( val ) )
        return 0;
    rval_release( val->vec->vals + index );
    rval_copy( val->vec->vals + index, item );
    return 1;
}

int rvec_push ( RVal * val, RVal * item ) {
    assert( val );
    if ( rval_type( val ) != RVT_VEC && !rvec_init( val, RILL_RVEC_DEFAULTSIZE ) )
        return 0;
    if ( !rvec_reserve( val, rvec_len( val ) + 1 ) )
        return 0;
    if ( !rval_exclude( val ) )
        return 0;
    RVal * dst = val->vec->vals + val->vec->len;
    rval_fzero( dst );
    rval_copy( dst, item );
    val->vec->len++;
    return 1;
}

int rvec_pop ( RVal * val ) {
    assert( val );
    assert( rval_type( val ) == RVT_VEC );
    if ( !rvec_len( val ) )
        return 0;
    if ( !rval_exclude( val ) )
        return 0;
    val->vec->len--;
    rval_release( val->vec->vals + val->vec->len );
    return 1;
}

int rvec_concat ( RVal * dst, RVal * src ) {
    assert( dst );
    assert( src );
    for ( size_t i = 0; i < rvec_len( src ); i++ )
        if ( !rvec_push( dst, rvec_get( src, i ) ) )
            return 0;
    return 1;
}

int rvec_fill ( RVal * dst, size_t n, RVal * item ) {
    assert( dst );
    assert( rval_type( dst ) == RVT_VEC );
    if ( !rvec_reserve( dst, n ) )
        return 0;
    rvec_clear( dst );
    for ( size_t i = 0; i < n; i++ ) {
        if ( !rvec_push( dst, item ) )
            return 0;
    }
    return 1;
}

int rvec_clear ( RVal * val ) {
    if ( rval_type( val ) != RVT_STR )
        return 0;
    if ( !rval_exclude( val ) )
        return 0;
    for ( size_t i = 0; i < rvec_len( val ); i++ )
        rval_release( val->vec->vals + i );
    val->vec->len = 0;
}

size_t __map_hash_hi ( const char * key ) {
    // TODO
}

size_t __map_hash_lo ( const char * key ) {
    // TODO
}

RMap * __map_create ( size_t cap ) {
    // TODO
}

int __rmap_resize ( RMap * map, size_t new_cap ) {
    // TODO
}

int __rmap_reserve ( RMap * map, size_t new_cap ) {
    // TODO
}

size_t __rmap_peek_hi ( RMap * map, RStr * key ) {
    // TODO
}

size_t __rmap_peek_lo ( RMap * map, RStr * key ) {
    // TODO
}

void __rmap_destroy ( RMap * map ) {
    // TODO
}

int rmap_init ( RVal * val, size_t init_cap ) {
    // TODO
}

int rmap_lease ( RVal * val ) {
    // TODO
}

int rmap_release ( RVal * val ) {
    // TODO
}

int rmap_reserve ( RVal * val, size_t init_cap ) {
    // TODO
}

int rmap_compact ( RVal * val ) {
    // TODO
}

size_t rmap_size ( RVal * val ) {
    // TODO
}

double rmap_load ( RVal * val ) {
    // TODO
}

RMapSlot * rmap_iter_begin ( RVal * map ) {
    // TODO
}

RMapSlot * rmap_iter_next ( RVal * map ) {
    // TODO
}

RVal * rmap_iter_key ( RMapSlot * iter ) {
    // TODO
}

RVal * rmap_iter_get ( RMapSlot * iter ) {
    // TODO
}

RVal * rmap_iter_set ( RMapSlot * iter, RVal * item ) {
    // TODO
}

RVal * rmap_iter_unset ( RMapSlot * iter ) {
    // TODO
}

RVal * rmap_get ( RVal * val, RVal * key ) {
    // TODO
}

int rmap_set ( RVal * val, RVal * key, RVal * item ) {
    // TODO
}

int rmap_unset ( RVal * val, RVal * key ) {
    // TODO
}

int rmap_clear ( RVal * val ) {
    // TODO
}

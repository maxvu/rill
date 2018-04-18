#include "rval.h"

int rval_init ( RVal * val, RValType type );
void rval_compact ( RVal * val );
RValType rval_type ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
void rval_release ( RVal * val );

static int rval_exclude ( RVal * val );

void rval_uxx_init ( RVal * val ) {
    val->type = UXX;
}

unsigned long rval_uxx_get ( const RVal * val ) {
    assert( val->type == UXX );
    return val->uxx;
}

void rval_uxx_set ( RVal * val, unsigned long u ) {
    assert( val->type == UXX );
    val->uxx = u;
}

void rval_uxx_copy ( RVal * dst, const RVal * src ) {
    assert( dst->type == UXX );
    assert( src->type == UXX );
    dst->uxx = src->uxx;
}

void rval_ixx_init ( RVal * val ) {
    val->type = IXX;
}

long rval_ixx_get ( const RVal * val ) {
    assert( val->type == IXX );
    return val->ixx;
}

void rval_ixx_set ( RVal * val, long i ) {
    assert( val->type == IXX );
    val->ixx = i;
}

void rval_ixx_copy ( RVal * dst, const RVal * src ) {
    assert( dst->type == IXX );
    assert( src->type == IXX );
    dst->ixx = src->ixx;
}

void rval_fxx_init ( RVal * val ) {
    val->type = FXX;
}

double rval_fxx_get ( const RVal * val ) {
    assert( val->type == FXX );
    return val->fxx;
}

void rval_fxx_set ( RVal * val, double f ) {
    assert( val->type == FXX );
    val->fxx = f;
}

void rval_fxx_copy ( RVal * dst, const RVal * src ) {
    assert( dst->type == FXX );
    assert( src->type == FXX );
    dst->fxx = src->fxx;
}

int rval_str_init ( RVal * val, size_t init_cap ) {
    val->type = STR;
    if ( !( val->str = malloc( sizeof( RStr ) ) ) )
        return 0;
    if ( init_cap < RILL_RVAL_STR_DEFAULTSIZE )
        init_cap = RILL_RVAL_STR_DEFAULTSIZE;
    assert( init_cap > 0 );
    if ( !( val->str->buf = malloc( sizeof( char * ) * ( init_cap + 1 ) ) ) ) {
        free( val->str );
        return 0;
    }
    val->str->ref = 1;
    val->str->buf[ 0 ] = 0;
    val->str->len = 0;
    val->str->cap = init_cap;
    return 1;
}

size_t rval_str_len ( const RVal * val ) {
    assert( val->type == STR );
    return val->str->len;
}

int rval_str_reserve ( RVal * val, size_t new_cap ) {
    assert( val->type == STR );
    if ( val->str->cap >= new_cap )
        return 1;
    if ( new_cap < RILL_RVAL_STR_DEFAULTSIZE )
        new_cap = RILL_RVAL_STR_DEFAULTSIZE;
    return rval_str_resize( val, new_cap * RILL_RVAL_STR_GROWTHFACTOR );
}

int rval_str_compact ( RVal * val ) {
    assert( val->type == STR );
    size_t target = val->str->len;
    if ( target < RILL_RVAL_STR_DEFAULTSIZE )
        target = RILL_RVAL_STR_DEFAULTSIZE;
    return rval_str_resize( val, target );
}

int rval_str_set ( RVal * dst, RVal * src ) {
    assert( dst->type == STR );
    assert( src->type == STR );
    rval_str_exclude( dst );
    rval_str_clear( dst );
    return rval_str_cat( dst, src );
}

int rval_str_cat ( RVal * dst, RVal * src ) {
    assert( dst->type == STR );
    assert( src->type == STR );
    rval_str_exclude( dst );
    if ( !src->str->len )
        return 1;
    if ( !rval_str_reserve( dst, dst->str->len + src->str->len ) )
        return 0;
    memcpy( dst->str->buf + dst->str->len, src->str->buf, src->str->len );
    dst->str->len += src->str->len;
    dst->str->buf[ dst->str->len ] = 0;
    return 1;
}

int rval_str_cmp ( const RVal * a, const RVal * b ) {
    assert( a->type == STR );
    assert( b->type == STR );
    return strcmp( a->str->buf, b->str->buf );
}

int rval_str_setc ( RVal * val, const char * cstr ) {
    assert( val->type == STR );
    assert( cstr );
    rval_str_exclude( val );
    rval_str_clear( val );
    return rval_str_catc( val, cstr );
}

int rval_str_catc ( RVal * val, const char * cstr ) {
    assert( val->type == STR );
    assert( cstr );
    rval_str_exclude( val );
    size_t cstr_len = strlen( cstr );
    if ( !rval_str_reserve( val, val->str->len + cstr_len ) )
        return 0;
    memcpy( val->str->buf + val->str->len, cstr, cstr_len );
    val->str->len += cstr_len;
    val->str->buf[ val->str->len ] = 0;
    return 1;
}

int rval_str_cmpc ( const RVal * val, const char * cstr ) {
    assert( val->type == STR );
    assert( cstr );
    return strcmp( val->str->buf, cstr );
}

void rval_str_clear ( RVal * val ) {
    assert( val->type == STR );
    rval_str_exclude( val );
    val->str->len = 0;
    val->str->buf[ 0 ] = 0;
}

int rval_str_copy ( RVal * dst, const RVal * src ) {
    assert( src->type == STR );
    dst->type = STR;
    dst->str = src->str;
    src->str->ref++;
}

void rval_str_release ( RVal * val ) {
    assert( val->type == STR );
    if ( !--val->str->ref ) {
        free( val->str->buf );
        free( val->str );
    }
    val->type = NIL;
}

static int rval_str_resize ( RVal * val, size_t new_cap ) {
    assert( val->type == STR );
    assert( new_cap > val->str->len );
    char * new_buf = malloc( sizeof( char ) * ( new_cap + 1 ) );
    if ( !new_buf )
        return 0;
    memcpy( new_buf, val->str->buf, val->str->len );
    new_buf[ val->str->len ] = 0;
    free( val->str->buf );
    val->str->buf = new_buf;
    val->str->cap = new_cap;
}

static int rval_str_exclude ( RVal * val ) {
    assert( val->type == STR );
    if ( val->str->ref == 1 )
        return 1;
    RVal tmp;
    if ( !rval_str_init( &tmp, val->str->len * RILL_RVAL_STR_GROWTHFACTOR ) )
        return 0;
    rval_str_set( &tmp, val );
    val->str->ref--;
    val->str = tmp.str;
    return 1;
}

int rval_vec_init ( RVal * val, size_t init_cap ) {

}

size_t rval_vec_len ( const RVal * vec );
int rval_vec_reserve ( RVal * vec, size_t new_cap );
int rval_vec_compact ( RVal * vec );
int rval_vec_push ( RVal * vec, RVal * item );
void rval_vec_pop ( RVal * vec );
RVal * rval_vec_get ( RVal * vec );
int rval_vec_set ( RVal * vec );
int rval_vec_append ( RVal * dst, const RVal * src );
void rval_vec_clear ( RVal * vec );
int rval_vec_copy ( RVal * dst, const RVal * src );
void rval_vec_release ( RVal * vec );

static int rval_vec_resize ( RVal * vec, size_t new_cap ) {

}

static int rval_vec_exclude ( RVal * vec );

int rval_map_init ( RVal * map );
size_t rval_map_size ( const RVal * map );
float rval_map_load ( const RVal * map );
int rval_map_reserve ( RVal * map );
int rval_map_compact ( RVal * map );
int rval_map_set ( RVal * map );
RVal * rval_map_get ( RVal * map );
void rval_map_unset ( RVal * map );
int rval_map_setc ( RVal * map );
RVal * rval_map_getc ( RVal * map );
void rval_map_unsetc ( RVal * map );
void * rval_map_iter_begin ( const RVal * map );
void * rval_map_iter_next ( const RVal * map );
const RVal * rval_map_iter_key ( void * iter );
RVal * rval_map_iter_val ( void * iter );
RVal * rval_map_iter_unset ( void * iter );
void rval_map_clear ( RVal * map );
int rval_map_copy ( RVal * dst, RVal * src );
void rval_map_release ( RVal * map );

static int rval_map_resize ( RVal * vec, size_t new_cap );
static int rval_map_exclude ( RVal * map );

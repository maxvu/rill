#ifndef RILL_RVAL
#define RILL_RVAL

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define RILL_RVAL_STR_DEFAULTSIZE 16
#define RILL_RVAL_STR_GROWTHFACTOR 2.0

#define RILL_RVAL_BUF_DEFAULTSIZE 16
#define RILL_RVAL_BUF_GROWTHFACTOR 2.0

#define RILL_RVAL_VEC_DEFAULTSIZE 8
#define RILL_RVAL_VEC_GROWTHFACTOR 2.0

#define RILL_RVAL_MAP_DEFAULTSIZE 12
#define RILL_RVAL_MAP_GROWTHFACTOR 2.0
#define RILL_RVAL_MAP_MAXLOAD 0.75

typedef enum RValType {
    NIL = 0,
    UXX = 1,
    IXX = 2,
    FXX = 3,
    STR = 4,
    VEC = 5,
    MAP = 6
} RValType;

typedef struct RVal RVal;
typedef struct RStr RStr;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef struct RVal {
    RValType type;
    union {
        unsigned long uxx;
        signed long   ixx;
        double        fxx;
        RStr *        str;
        RVec *        vec;
        RMap *        map;
    };
} RVal;

typedef struct RStr {
    size_t ref;
    size_t len;
    size_t cap;
    char * buf;
} RStr;

typedef struct RVec {
    size_t ref;
    size_t len;
    size_t cap;
    RVal * arr;
} RVec;

typedef struct RMapSlot {
    RVal key;
    RVal val;
} RMapSlot;

typedef struct RMap {
    size_t ref;
    size_t cap;
    size_t occ;
    RMapSlot * slots;
} RMap;

/*
    RVal generic functions.
*/

int rval_init ( RVal * val, RValType type );
void rval_compact ( RVal * val );
RValType rval_type ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
void rval_release ( RVal * val );

/*
    RVal generic functions - implementation.
*/

static int rval_exclude ( RVal * val );

/*
    UXX RVal functions.
*/

void rval_uxx_init ( RVal * val );
unsigned long rval_uxx_get ( const RVal * uxx );
void rval_uxx_set ( RVal * val, unsigned long u );
void rval_uxx_copy ( RVal * dst, const RVal * src );

/*
    IXX RVal functions.
*/

void rval_ixx_init ( RVal * val );
long rval_ixx_get ( const RVal * val );
void rval_ixx_set ( RVal * val, long i );
void rval_ixx_copy ( RVal * dst, const RVal * src );

/*
    FXX RVal functions.
*/

void rval_fxx_init ( RVal * val );
double rval_fxx_get ( const RVal * val );
void rval_fxx_set ( RVal * val, double f );
void rval_fxx_copy ( RVal * dst, const RVal * src );

/*
    STR RVal functions.
*/

int rval_str_init ( RVal * val, size_t init_cap );
size_t rval_str_len ( const RVal * val );
int rval_str_reserve ( RVal * val, size_t new_cap );
int rval_str_compact ( RVal * val );
int rval_str_set ( RVal * dst, RVal * src );
int rval_str_cat ( RVal * dst, RVal * src );
int rval_str_cmp ( const RVal * a, const RVal * b );
int rval_str_setc ( RVal * val, const char * cstr );
int rval_str_catc ( RVal * val, const char * cstr );
int rval_str_cmpc  ( const RVal * val, const char * cstr );
void rval_str_clear ( RVal * val );
int rval_str_copy ( RVal * dst, const RVal * src );
void rval_str_release ( RVal * val );

static int rval_str_resize ( RVal * val, size_t new_cap );
static int rval_str_exclude ( RVal * val );

/*
    VEC RVal functions.
*/

int rval_vec_init ( RVal * val, size_t init_cap );
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

static int rval_vec_resize ( RVal * vec, size_t new_cap );
static int rval_vec_exclude ( RVal * vec );

/*
    MAP RVal functions.
*/

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

#endif

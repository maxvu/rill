#ifndef RILL_RVAL
#define RILL_RVAL

#define RILL_RVAL_STR_DEFAULTSIZE 16
#define RILL_RVAL_STR_GROWTHFACTOR 2.0

#define RILL_RVAL_VEC_DEFAULTSIZE 8
#define RILL_RVAL_VEC_GROWTHFACTOR 2.0

#define RILL_RVAL_MAP_DEFAULTSIZE 12
#define RILL_RVAL_MAP_GROWTHFACTOR 2.0
#define RILL_RVAL_MAP_MAXLOAD 0.8

#include <stddef.h>

typedef enum RValType {
    NONE = 0,
    UXX  = 1,
    IXX  = 2,
    FXX  = 3,
    BUF  = 4,
    STR  = 5,
    VEC  = 6,
    MAP  = 7
} RValType;

typedef struct RVal RVal;
typedef struct RBuf RBuf;
typedef struct RVec RVec;
typedef struct RMapSlot RMapSlot;
typedef struct RMap RMap;

typedef RMapSlot * RMapIter;

typedef struct RVal {
    RValType type;
    size_t refcount;
    RVal * up;
    union {
        unsigned long uxx;
        long          ixx;
        double        fxx;
        char *        buf;
        RVec *        vec;
        RMap *        map;
    } data;
} RVal;

typedef struct RBuf {
    size_t len;
    size_t cap;
    char * buf;
} RBuf;

typedef struct RVec {
    size_t len;
    size_t cap;
    RVal buf[];
} RVec;

typedef struct RMapSlot {
    RVal * key;
    RVal * val;
} RMapSlot;

typedef struct RMap {
    size_t occ;
    size_t cap;
    RMapSlot slots[];
} RMap;

RVal * rval_create ( RValType type );
int rval_init ( RVal * val, RValType type );
RVal * rval_clone ( RVal * val );
void rval_ref  ( RVal * val );
void rval_deref  ( RVal * val );
void rval_retire ( RVal * val );
void rval_destroy ( RVal * val );

void rval_uxx_init ( RVal * val, unsigned long uxx );
unsigned long rval_uxx_get ( RVal * uxx );
void rval_uxx_set ( RVal * uxx, unsigned long u );

void rval_ixx_init ( RVal * val, long uxx );
long rval_ixx_get ( RVal * ixx );
void rval_ixx_set ( RVal * ixx, long i );

void rval_fxx_init ( RVal * val, double uxx );
double rval_fxx_get ( RVal * fxx );
void rval_fxx_set ( RVal * fxx, double f );

int rval_buf_init ( RVal * val, size_t init_cap );
size_t rval_buf_len ( RVal * buf );
int rval_buf_reserve ( RVal * buf, size_t new_cap );
int rval_buf_compact ( RVal * buf );
int rval_buf_set ( RVal * buf, RVal * other );
int rval_buf_cat ( RVal * buf, RVal * other );
int rval_buf_cmp ( RVal * buf, RVal * other );
int rval_buf_setc ( RVal * buf, const char * other, size_t len );
int rval_buf_catc ( RVal * buf, const char * other, size_t len );
int rval_buf_cmpc ( RVal * buf, const char * other, size_t len );
void rval_buf_clear ( RVal * buf );
RVal * rval_buf_clone ( RVal * buf );
void rval_buf_retire ( RVal * buf );

int rval_str_init ( RVal * val, size_t init_cap );
size_t rval_str_len ( RVal * str );
int rval_str_reserve ( RVal * str, size_t new_cap );
int rval_str_compact ( RVal * str );
int rval_str_set ( RVal * str, RVal * other );
int rval_str_cat ( RVal * str, RVal * other );
int rval_str_cmp ( RVal * str, RVal * other );
int rval_str_setc ( RVal * str, const char * other );
int rval_str_catc ( RVal * str, const char * other );
int rval_str_cmpc ( RVal * str, const char * other );
void rval_str_clear ( RVal * str );
RVal * rval_str_clone ( RVal * str );
void rval_str_retire ( RVal * str );

int rval_vec_init ( RVal * val, size_t init_cap );
size_t rval_vec_size ( RVal * vec );
int rval_reserve ( RVal * vec, size_t new_cap );
int rval_compact ( RVal * vec );
int rval_vec_push ( RVal * vec, RVal * item );
int rval_vec_pop ( RVal * vec );
RVal * rval_vec_get ( RVal * vec, size_t index );
RVal * rval_vec_set ( RVal * vec, size_t index, RVal * item );
void rval_vec_clear ( RVal * vec );
RVal * rval_vec_clone ( RVal * str );
void rval_vec_retire ( RVal * vec );

int rval_map_init ( RVal * map );
size_t rval_map_size ( RVal * map );
float rval_map_load ( RVal * map );
int rval_map_reserve ( RVal * map, size_t new_cap );
int rval_map_compact ( RVal * map );
int rval_map_set ( RVal * map, RVal * key, RVal * val );
RVal * rval_map_get ( RVal * map, RVal * key );
void rval_map_unset ( RVal * map, RVal * key );
int rval_map_setc ( RVal * map, const char * key, RVal * val );
RVal * rval_map_getc ( RVal * map, const char * key );
void rval_map_unsetc ( RVal * map, const char * key );
RMapIter * rval_map_iter_begin ( RVal * map );
RMapIter * rval_map_iter_next ( RMapIter * map );
const RVal * rval_map_iter_key ( RMapIter * map );
const RVal * rval_map_iter_val ( RMapIter * map );
void rval_map_clear ( RVal * map );
RVal * rval_map_clone ( RVal * map );
void rval_map_retire ( RVal * map );

#endif

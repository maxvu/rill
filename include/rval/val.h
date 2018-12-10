#ifndef RILL_RVAL_RVAL
#define RILL_RVAL_RVAL

#include "config.h"
#include "rval/slab.h"

#include <stdint.h>

typedef enum RValType {
    RVT_NIL = 0,
    RVT_UXX = 1,
    RVT_IXX = 2,
    RVT_FXX = 3,
    RVT_BUF = 4,
    RVT_VEC = 5,
    RVT_MAP = 6
} RValType;

typedef struct RVal {
    RValType type;
    union {
        RILL_UXX_TYPE uxx;
        RILL_IXX_TYPE ixx;
        RILL_FXX_TYPE fxx;
        Slab        * slb;
    };
} RVal;

RVal rval_qnil ();
RVal rval_quxx ( RILL_UXX_TYPE u );
RVal rval_qixx ( RILL_IXX_TYPE i );
RVal rval_qfxx ( RILL_FXX_TYPE f );
RVal rval_qbuf ( size_t init_cap );
RVal rval_qvec ( size_t init_cap );
RVal rval_qmap ( size_t init_cap );

int rval_type ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
void rval_swap ( RVal * a, RVal * b );
int rval_clone ( RVal * dst, RVal * src );
void rval_move ( RVal * dst, RVal * src );
void rval_lease ( RVal * val );
void rval_release ( RVal * val );
int rval_exclude ( RVal * val );
int rval_cycles ( RVal * haystack, RVal * needle );
int rval_isfw ( RVal * val );
int rval_isnil ( RVal * val );
int rval_isnatrec ( RVal * val );
int rval_istruthy ( RVal * val );
int rval_eq ( RVal * val );
int rval_serialize ( RVal * dstbuf, RVal * val );
void rval_dump ( RVal * val );

void ruxx_set ( RVal * val, RILL_UXX_TYPE u );
RILL_UXX_TYPE ruxx_get ( RVal * val );

void rixx_set ( RVal * val, RILL_IXX_TYPE i );
RILL_IXX_TYPE rixx_get ( RVal * val );

int rfxx_isfinite ( RVal * val );
int rfxx_isnan ( RVal * val );
int rfxx_isinf ( RVal * val );
int rfxx_isninf ( RVal * val );
void rfxx_set ( RVal * val, RILL_FXX_TYPE f );
RILL_FXX_TYPE rfxx_get ( RVal * val );

#define RILL_RBUF_MINSIZE 8
#define RILL_RBUF_DEFAULTSIZE 8
#define RILL_RBUF_GROWTHCOEFF 2.0

int rbuf_init ( RVal * val, size_t init_cap );

size_t rbuf_len ( RVal * buf );
size_t rbuf_cap ( RVal * buf );
int rbuf_reserve ( size_t new_cap );
int rbuf_compact ( RVal * buf );

int rbuf_clone ( RVal * dst, RVal * src );
void rbuf_lease ( RVal * buf );
void rbuf_release ( RVal * buf );

int rbuf_cpy ( RVal * dst, RVal * src );
int rbuf_cat ( RVal * dst, RVal * src );
int rbuf_cmp ( RVal * a, RVal * b );

int rbuf_cpyc ( RVal * dst, char * cstr );
int rbuf_catc ( RVal * dst, char * cstr );
int rbuf_cmpc ( RVal * dst, char * cstr );

int rbuf_cpyraw ( RVal * dst, uint8_t * raw, size_t raw_len );
int rbuf_catraw ( RVal * dst, uint8_t * raw, size_t raw_len );
int rbuf_cmpraw ( RVal * dst, uint8_t * raw, size_t raw_len );

int rbuf_substr ( RVal * dst, RVal * src, size_t n );
int rbuf_clear ( RVal * buf );

#define RILL_RVEC_MINSIZE 2
#define RILL_RVEC_DEFAULTSIZE 16
#define RILL_RVEC_GROWTHCOEFF 2.0

int rvec_init ( RVal * val, size_t init_cap );

size_t rvec_len ( RVal * vec );
size_t rvec_cap ( RVal * vec );
int rvec_reserve ( RVal * vec, size_t new_cap );
int rvec_compact ( RVal * vec );

int rvec_clone ( RVal * dst, RVal * src );
int rvec_eq ( RVal * a, RVal * b );
void rvec_lease ( RVal * vec );
void rvec_release ( RVal * vec );

RVal * rvec_get ( RVal * vec, size_t index );
int rvec_set ( RVal * vec, size_t index, RVal * item );
int rvec_insert ( RVal * vec, size_t index, RVal * item );
int rvec_push ( RVal * vec, RVal * item );
int rvec_pop ( RVal * vec );
int rvec_fill ( RVal * vec, size_t start_index, RVal * item, size_t n );

int rvec_clear ( RVal * vec );

#define RILL_RMAP_MINSIZE 12
#define RILL_RMAP_DEFAULTSIZE 16
#define RILL_RMAP_GROWTHCOEFF 2.0

int rmap_init ( RVal * val, size_t init_cap );

size_t rmap_size ( RVal * map );
double rmap_load ( RVal * map );
int rmap_reserve ( RVal * map, size_t new_cap );
int rmap_compact ( RVal * map );

int rmap_clone ( RVal * dst, RVal * src );
int rmap_eq ( RVal * a, RVal * b );
void rmap_lease ( RVal * map );
void rmap_release ( RVal * map );

RVal * rmap_get ( RVal * map, RVal * key );
int rmap_set ( RVal * map, RVal * key, RVal * val );
int rmap_unset ( RVal * map, RVal * key );

void rmap_clear ( RVal * map );

typedef RVal * RMapIter;
RMapIter rmap_begin ( RVal * map );
RMapIter rmap_end ( RVal * map );
RMapIter rmap_iter_next ( RVal * map, RMapIter it );
const RVal * rmap_iter_key ( RMapIter it );
RVal * rmap_iter_val ( RMapIter it );

#endif

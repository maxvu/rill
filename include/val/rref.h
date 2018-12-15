#ifndef RVAL_VAL_RREF
#define RVAL_VAL_RREF

#include "config.h"

#include <stddef.h>

typedef enum {
    RRT_NIL = 0,
    RRT_IXX = 1,
    RRT_UXX = 2,
    RRT_FXX = 3,
    RRT_BUF = 4,
    RRT_VEC = 5,
    RRT_MAP = 6
} RRefType;

typedef struct rbuffer RBuffer;
typedef struct rvector RVector;
typedef struct rhashmap RHashMap;

typedef struct rref {
    RRefType type;
    union {
        RILL_IXX_TYPE ixx;
        RILL_UXX_TYPE uxx;
        RILL_FXX_TYPE fxx;
        RBuffer *     buf;
        RVector *     vec;
        RHashMap *    map;
    };
} RRef;

RRefType rref_type ( RRef * ref );
int rref_settype ( RRef * ref, RRefType type );
uint8_t rref_rttype ( RRef * ref );
uint8_t rref_setrttype ( RRef * ref );
int rref_copy ( RRef * dst, RRef * src );
int rref_move ( RRef * dst, RRef * src );
int rref_swap ( RRef * a, RRef * b );
int rref_clone ( RRef * dst, RRef * src );
int rref_contains ( RRef * haystack, RRef * needle );
void rref_lease ( RRef * ref );
void rref_release ( RRef * ref );
void rref_dump ( RRef * ref );

RRef rref_ixx ( RILL_IXX_TYPE i );
RILL_IXX_TYPE rixx_get ( RRef * ref );
void rixx_set ( RRef * ref, RILL_IXX_TYPE i );

RRef rref_uxx ( RILL_UXX_TYPE i );
RILL_UXX_TYPE ruxx_get ( RRef * ref );
void ruxx_set ( RRef * ref, RILL_UXX_TYPE u );

RRef rref_fxx ( RILL_FXX_TYPE f );
RILL_FXX_TYPE rfxx_get ( RRef * ref );
void rfxx_set ( RRef * ref, RILL_FXX_TYPE f );
void rfxx_finite ( RRef * ref );

RRef rref_buf ( size_t init_cap );
size_t rbuf_len ( RRef * buf );
int rbuf_reserve ( RRef * buf, size_t new_cap );
int rbuf_compact ( RRef * buf );
uint8_t * rbuf_get ( RRef * buf );
int rbuf_cpy ( RRef * dst, RRef * src );
int rbuf_cat ( RRef * dst, RRef * src );
int rbuf_cmp ( RRef * dst, RRef * src );
int rbuf_cpyc ( RRef * buf, const char * cstr );
int rbuf_catc ( RRef * buf, const char * cstr );
int rbuf_cmpc ( RRef * buf, const char * cstr );
int rbuf_repeat ( RRef * buf, size_t n );
void rbuf_zero ( RRef * buf );
int rbuf_substr ( RRef * dst, RRef * src_buf );
void rbuf_clear ( RRef * buf );

RRef rref_vec ( size_t init_cap );
int rvec_reserve ( RRef * ref, size_t new_cap );
int rvec_compact ( RRef * ref );
size_t rvec_len ( RRef * ref );
int rvec_get ( RRef * ref, size_t index );
int rvec_set ( RRef * ref, size_t index, RRef * val );
int rvec_push ( RRef * ref, RRef * val );
int rvec_pop ( RRef * ref );
int rvec_fill ( RRef * ref, size_t n, RRef * val );
void rvec_clear ( RRef * ref );

RRef rref_map ( size_t init_cap );
size_t rmap_len ( RRef * ref );
RRef * rmap_get ( RRef * ref, RRef * key );
int rmap_set ( RRef * ref, RRef * key, RRef * val );
int rmap_merge ( RRef * a, RRef * b );
int rmap_intersect ( RRef * a, RRef * b );
int rmap_unset ( RRef * ref, RRef * key );
void rmap_clear ( RRef * ref );

#endif

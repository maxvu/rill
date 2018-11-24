#ifndef RILL_RVAL
#define RILL_RVAL

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: make sure that allocations fail "atomically" with _move().
// TODO: make _copy() return void.

typedef struct RStr RStr;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef enum RValType {
    RVT_NIL = 0,
    RVT_UXX = 1,
    RVT_IXX = 2,
    RVT_FXX = 3,
    RVT_STR = 4,
    RVT_VEC = 5,
    RVT_MAP = 10
} RValType;

typedef struct RVal {
    enum RValType type;
    union {
        unsigned long uxx;
        long          ixx;
        double        fxx;
        RStr *        str;
        RVec *        vec;
        RMap *        map;
    };
} RVal;

void rval_fzero ( RVal * val );
RValType rval_type ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
int rval_move ( RVal * dst, RVal * src );
int rval_swap ( RVal * a, RVal * b );
int rval_clone ( RVal * dst, RVal * src );
int rval_exclude ( RVal * val );
int rval_contains ( RVal * haystack, RVal * needle );
int rval_compact ( RVal * val );
int rval_lease ( RVal * val );
int rval_release ( RVal * val );
int rval_cmp ( RVal * a, RVal * b );
int rval_eq ( RVal * a, RVal * b );
void rval_dump ( RVal * val );

unsigned long ruxx_get ( RVal * val );
void ruxx_set ( RVal * val, unsigned long u );

long rixx_get ( RVal * val );
void rixx_set ( RVal * val, long i );

double rfxx_get ( RVal * val );
void rfxx_set ( RVal * val, double f );

#define RILL_RSTR_MINSIZE 3
#define RILL_RSTR_GROWTHCOEFF 2.0

typedef struct RStr {
    char * buffer;
    size_t refcount;
    size_t len;
    size_t cap;
} RStr;

RStr * __rstr_create ( size_t cap );
int __rstr_resize ( RStr * str, size_t new_cap );
int __rstr_reserve ( RStr * str, size_t new_cap );
int __rstr_cat ( RStr * str, const char * src, size_t len );
void __rstr_destroy ( RStr * str );

int rstr_init ( RVal * val, size_t init_cap );
void rstr_lease ( RVal * val );
void rstr_release ( RVal * val );
int rstr_reserve ( RVal * val, size_t new_cap );
int rstr_compact ( RVal * val );
size_t rstr_len ( RVal * val );
const char * rstr_get ( RVal * val );
int rstr_copy ( RVal * dst, RVal * src );
int rstr_cat ( RVal * dst, RVal * src );
int rstr_cmp ( RVal * a, RVal * b );
int rstr_clear ( RVal * val );
int rstr_setc ( RVal * dst, const char * src, size_t src_len );
int rstr_catc ( RVal * dst, const char * src, size_t src_len );
int rstr_cmpc ( RVal * dst, const char * src, size_t src_len );

#define RILL_RVEC_MINSIZE 3
#define RILL_RVEC_DEFAULTSIZE 16
#define RILL_RVEC_GROWTHCOEFF 2.0

typedef struct RVec {
    RVal * vals;
    size_t refcount;
    size_t len;
    size_t cap;
} RVec;

RVec * __rvec_create ( size_t cap );
int __rvec_resize ( RVec * vec, size_t new_cap );
int __rvec_reserve ( RVec * vec, size_t new_cap );
int __rvec_set ( RVec * vec, size_t index, RVal * item );
void __rvec_destroy ( RVec * vec );

int rvec_init ( RVal * vec, size_t init_cap );
void rvec_lease ( RVal * vec );
void rvec_release ( RVal * vec );
int rvec_reserve ( RVal * vec, size_t new_cap );
int rvec_compact ( RVal * vec );
int rvec_copy ( RVal * dst, RVal * src );
size_t rvec_len ( RVal * vec );
RVal * rvec_get ( RVal * vec, size_t index );
int rvec_set ( RVal * vec, size_t index, RVal * item );
int rvec_push ( RVal * vec, RVal * item );
int rvec_pop ( RVal * vec );
int rvec_concat ( RVal * dst, RVal * src );
int rvec_fill ( RVal * dst, size_t n, RVal * item );
int rvec_clear ( RVal * vec );

#define RILL_RMAP_MINCAP 8
#define RILL_RMAP_MAXLOAD 0.85
#define RILL_RMAP_GROWTHCOEFF 2.0

typedef struct RMapSlot {
    RVal key;
    RVal val;
} RMapSlot;

typedef struct RMap {
    RMapSlot * slots;
    size_t refcount;
    size_t len;
    size_t cap;
} RMap;

RMap * __rmap_create ( size_t init_cap );
size_t __rmap_find_hi ( RMap * map, RVal * key );
size_t __rmap_find_lo ( RMap * map, RVal * key );
int __rmap_resize ( RMap * map, size_t new_cap );
int __rmap_set ( RMap * map, RVal * key, RVal * val );
void __rmap_unset ( RMap * map, size_t index );
void __rmap_destroy ( RMap * map );

int rmap_init ( RVal * val, size_t init_cap );
int rmap_lease ( RVal * map );
int rmap_release ( RVal * map );
int rmap_reserve ( RVal * map, size_t new_cap );
int rmap_compact ( RVal * map );
int rmap_set ( RVal * map, RVal * key, RVal * val );
int rmap_unset ( RVal * map, RVal * key );
int rmap_clear ( RVal * map );
int rmap_keys ( RVal * dst_lst, RVal * src_map );
int rmap_vals ( RVal * dst_lst, RVal * src_map );

#endif

#ifndef RILL_RVAL
#define RILL_RVAL

#include <stddef.h>

enum RValType {
    NIL = 0,
    UXX = 1,
    IXX = 2,
    DBL = 3,
    STR = 4,
    VEC = 5,
    MAP = 10
};

typedef struct RVec RVec;
typedef struct RMap RMap;

typedef struct RVal {
    RValType type;
    union {
        unsigned long uxx;
        signed long   ixx;
        double        dbl;
        RStr *        str;
        RVec *        vec;
        RMap *        map;
    };
} RVal;

typedef struct RStr {
    char * buf;
    size_t len;
    size_t cap;
    size_t refcount;
} RStr;

typedef struct RVec {
    RVal * vals;
    size_t len;
    size_t cap;
    size_t refcount;
    RVal * up;
} RVec;

typedef struct RMapSlot {
    RVal * key;
    RVal * val;
} RMapSlot;

typedef struct RMap {
    RMapSlot * slots;
    size_t len;
    size_t cap;
    size_t refcount;
    RVal * up;
} RMap;

RVal * rval_create ( RValType type );
void rval_destroy ( RVal * val );

void rval_zero ( RVal * val );
int rval_lease ( RVal * val );
void rval_clear ( RVal * val );
int rval_compact ( RVal * val );
int rval_exclude ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
int rval_clone ( RVal * dst, RVal * src );
int rval_descends ( RVal * needle, RVal * haystack );

int rstr_init ( RVal * str, size_t init_cap );
void rstr_retire ( RVal * str );
int rstr_reserve ( RVal * str, size_t new_cap );
int rstr_compact ( RVal * str );
size_t rstr_len ( RVal * str, RVal * other );
const char * rstr_cstr ( RVal * str );
int rstr_set ( RVal * str, RVal * other );
int rstr_cat ( RVal * str, RVal * other );
int rstr_cmp ( RVal * str, RVal * other );
int rstr_setc ( RVal * str, const char * cstr );
int rstr_catc ( RVal * str, const char * cstr );
int rstr_cmpc ( RVal * str, const char * cstr );
void rstr_clear ( RVal * str );

int rvec_init ( RVal * val, size_t init_cap );
void rvec_retire ( RVal * vec );
int rvec_reserve ( RVal * vec, size_t new_cap );
int rvec_compact ( RVal * vec );
int rvec_copy ( RVal * dst, RVal * src );
int rvec_clone ( RVal * dst, RVal * src );
size_t rvec_len ( RVal * vec );
RVal * rvec_get ( RVal * vec, size_t index );
int rvec_set ( RVal * vec, size_t index, const RVal * item );
int rvec_push ( RVal * vec, RVal * item );
void rvec_pop ( RVec * vec );
void rvec_clear ( RVec * vec );

int rmap_init ( RVal * val, size_t init_cap );
void rmap_retire ( RVal * map );
int rmap_reserve ( RVal * map, size_t new_cap );
int rmap_compact ( RVal * map );
int rmap_copy ( RVal * dst, RVal * src );
int rmap_clone ( RVal * dst, RVal * src );
size_t rmap_size ( RVal * map );
RVal * rmap_get ( RVal * map, RVal * key );
int rmap_set ( RVal * map, RVal * key, RVal * item );
int rmap_unset ( RVal * map, RVal * key );
RVal * rmap_getc ( RVal * map, const char * key );
int rmap_setc ( RVal * map, const char * key, RVal * item );
int rmap_unsetc ( RVal * map, const char * key );
RMapSlot * rmap_iterbegin ( RVal * map );
RMapSlot * rmap_iternext ( RVal * map, RMapSlot * iter );
RVal * rmap_iterkey ( RMapSlot * slot );
RVal * rmap_iterval ( RMapSlot * slot );
int rmap_clear ( RVal * val );

#endif

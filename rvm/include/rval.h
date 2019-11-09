#ifndef RILL_RVAL
#define RILL_RVAL

#include "common.h"

typedef enum rvtyp {
    RVT_NUM = 0,
    RVT_STR = 1,
    RVT_VEC = 2,
    RVT_MAP = 3,
    RVT_PIP = 4,
    RVT_UDO = 5
} rvtyp;

#ifdef RILL_32BIT
    typedef struct rval {
        rvtyp typ : 3;
        uxx_t ref : 8;
        uxx_t tag : 21;
    } rval;
#endif

#ifdef RILL_64BIT
    typedef struct rval {
        rvtyp typ : 3;
        uxx_t ref : 8;
        uxx_t tag : 53;
    } rval;
#endif

rvtyp rval_type     ( rval * val );
rerr  rval_copy     ( rval ** dst, rval * src );
rerr  rval_clone    ( rval ** dst, rval * src );
rerr  rval_compact  ( rval * val );
char  rval_contains ( rval * haystack, rval * needle );
char  rval_tag      ( rval * val, uxx_t tag );
rerr  rval_ref      ( rval * val );
rerr  rval_deref    ( rval * val );

typedef struct rnum {
    rval tag;
    union {
        ixx_t ixx;
        uxx_t uxx;
        fxx_t fxx;
    };
} rnum;

rval  * rnum_create ();
ixx_t * rnum_geti ( rval * num );
uxx_t * rnum_getu ( rval * num );
fxx_t * rnum_getf ( rval * num );

typedef struct rstr {
    rval   tag;
    uxx_t  len;
    uxx_t  cap;
    char * buf;
} rstr;

rval * rstr_create   ();
uxx_t  rstr_len      ( rval * str );
rerr   rstr_reserve  ( rval * str. uxx_t new_cap );
rerr   rstr_compact  ( rval * str );
char * rstr_get      ( rval * str );
rerr   rstr_set      ( rval * dst, rval * src );
rerr   rstr_cat      ( rval * dst, rval * src );
rerr   rstr_setc     ( rval * str, const char * src );
rerr   rstr_catc     ( rval * str, const char * src );
rerr   rstr_substr   ( rval * dst, rval * src, uxx_t bgn, uxx_t len );
rerr   rstr_reverse  ( rval * str );
rerr   rstr_clear    ( rval * str );

typedef struct rvec {
    rval   tag;
    uxx_t  len;
    uxx_t  cap;
    rval * vls;
} rvec;

rval * rvec_create   ();
uxx_t  rvec_len      ( rval * vec );
rerr   rvec_reserve  ( rval * vec, uxx_t new_cap );
rerr   rvec_compact  ( rval * vec );
rerr   rvec_push     ( rval * vec, rval * item );
rerr   rvec_pop      ( rval * vec );
rval * rvec_get      ( rval * vec, uxx_t idx );
rerr   rvec_set      ( rval * vec, uxx_t idx, rval * item );
rval * rvec_front    ( rval * vec );
rval * rvec_back     ( rval * vec );
rerr   rvec_shift    ( rval * vec );
rerr   rvec_unshift  ( rval * vec, rval * item );
rerr   rvec_reverse  ( rval * vec );
rerr   rvec_concat   ( rval * dst, rval * src );
rerr   rvec_clear    ( rval * vec );

typedef struct rmap {
    rval   tag;
    uxx_t  len;
    uxx_t  occ;
    rval * kvp;
} rmap;

rval * rmap_create  ();
uxx_t  rmap_size    ( rval * map );
rerr   rmap_reserve ( rval * map, uxx_t new_cap );
rerr   rmap_compact ( rval * map );
rerr   rmap_set     ( rval * map, rval * key, rval * val );
rval * rmap_get     ( rval * map, rval * key );
rerr   rmap_unset   ( rval * map, rval * key );
rval * rmap_getc    ( rval * map, const char * key );
rerr   rmap_setc    ( rval * map, const char * key, rval * val );
rerr   rmap_unsetc  ( rval * map, const char * key );
rerr   rmap_keys    ( rval * dst, rval * map );
rerr   rmap_vals    ( rval * dst, rval * map );
rerr   rmap_merge   ( rval * dst, rval * src );
rerr   rmap_clear   ( rval * map );

#endif

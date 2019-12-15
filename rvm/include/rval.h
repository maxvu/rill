#ifndef RILL_RVAL
#define RILL_RVAL

#include "rerr.h"
#include "platform.h"

typedef enum rtyp {
    TYP_NIL = 0,
    TYP_IXX = 1,
    TYP_UXX = 2,
    TYP_FXX = 3,
    TYP_STR = 4,
    TYP_VEC = 5,
    TYP_MAP = 6,
    TYP_EXT = 7
} rtyp;

typedef struct rval {
    UXX hed;
    UXX ref;
} rval;

typedef struct rnum {
    rval hed;
    union {
        IXX ixx;
        UXX uxx;
        FXX fxx;
    };
} rnum;

typedef struct rstr {
    rval   hed;
    char * buf;
    UXX    len;
    UXX    cap;
} rstr;

typedef struct rvec {
    rval   hed;
    rval * vls;
    UXX    len;
    UXX    cap;
} rvec;

typedef struct rmap {
    rval   hed;
    rval * ety;
    UXX    siz;
    UXX    cap;
} rmap;

typedef struct rext {
    rval hed;

} rext;

rerr rval_type ( rval * val );
rerr rval_tag ( rval * val );
rerr rval_settag ( rval * val, UXX new_tag );
rerr rval_ref ( rval * val );
rerr rval_deref ( rval * val );
rerr rval_clone ( rval * dst, rval * src );
rerr rval_cycles ( rval * hay, rval * needle );
rerr rval_eq ( rval * a, rval * b );

rerr rnum_seti ( rval * num, IXX i );
IXX rnum_geti ( rval * num );
rerr rnum_setu ( rval * num, UXX u );
UXX rnum_getu ( rval * num );
rerr rnum_setf ( rval * num, FXX f );
FXX rnum_getf ( rval * num );

rval * rstr_create ( UXX init_cap );
rerr rstr_len ( rval * str );
rerr rstr_reserve ( rval * str );
rerr rstr_compact ( rval * str );
rerr rstr_cat ( rval * str );
rerr rstr_cmp ( rval * str );
rerr rstr_get ( rval * str );
rerr rstr_empty ( rval * str );

rval * rvec_create ( UXX init_cap );
UXX rvec_len ( rval * vec );
rerr rvec_reserve ( rval * vec, UXX new_cap );
rerr rvec_compact ( rval * vec );
rerr rvec_push ( rval * vec, rval * itm );
rerr rvec_pop ( rval * vec );
rerr rvec_concat ( rval * vec );
rerr rvec_reverse ( rval * vec );
rerr rvec_sort ( rval * vec );
rerr rvec_shuffle ( rval * vec );
rerr rvec_clear ( rval * vec );

rval * rmap_create ( UXX init_cap );
UXX rmap_size ( rval * map );
rerr rmap_has ( rval * map, rval * key );
rval * rmap_get ( rval * map, rval * key );
rerr rmap_set ( rval * map, rval * key, rval * val );
rerr rmap_unset ( rval * map );
rerr rmap_keys ( rval * dst, rval * map );
rerr rmap_vals ( rval * dst, rval * map );
rerr rmap_clear ( rval * map );

typedef rval * rmapit;

rmapit rmap_begin ( rval * map );

rval * rmapit_key ( rmapit it );
rval * rmapit_val ( rmapit it );
rmapit rmapit_next ( rmapit it );
rmapit rmapit_del ( rmapit it );
rerr   rmapit_ok ( rmapit it );

#endif

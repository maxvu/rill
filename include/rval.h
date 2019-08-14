#ifndef RILL_RVAL
#define RILL_RVAL

typedef enum rval_type {
    RVT_NIL,
    RVT_NUM,
    RVT_VEC,
    RVT_MAP,
    RVT_UDO
} rval_type;

typedef struct rval rval;
typedef struct rint rint;
typedef struct rrat rrat;
typedef struct rstr rstr;
typedef struct rvec rvec;
typedef struct rmap rmap;

unsigned long rval_type ( rval * val );
unsigned long rval_tag ( rval * val );
rerr rval_settag ( rval * val, unsigned long tag );
rerr rval_contains ( rval * hay, rval * ndl );
rerr rval_ref ( rval * val );
rerr rval_deref ( rval * val );
rerr rval_truthy ( rval * val );
rerr rval_copy ( rval ** dst, rval * src );
rerr rval_clone ( rval ** dst, rval * src );
rerr rval_swap ( rval ** a, rval ** b );
rerr rval_eq ( rval * a, rval * b );
rstr * rval_tostr ( rval * val );

rnum * rnum_create ();
rerr rnum_add ( rnum * dst, rnum * a, rnum * b );
rerr rnum_sub ( rnum * dst, rnum * a, rnum * b );
rerr rnum_mul ( rnum * dst, rnum * a, rnum * b );
rerr rnum_div ( rnum * dst, rnum * a, rnum * b );
rerr rnum_neg ( rnum * num );
rerr rnum_abs ( rnum * num );
rerr rnum_cmp ( rnum * a, rnum * b );
rerr rnum_cmpi ( rnum * a, long i );
rerr rnum_cmpu ( rnum * a, unsigned long u );
rerr rnum_eq ( rnum * a, rnum * b );
rerr rnum_set ( rnum * dst, rnum * src );
rerr rnum_seti ( rnum * dst, long i );
rerr rnum_setu ( rnum * dst, unsigned long i );
rerr rnum_setf ( rnum * dst, double f );
rerr rnum_sets ( rnum * dst, const char * c );
rerr rnum_compact ( rnum * num );
double rnum_getd ( rnum * num );
rstr * rnum_gets ( rnum * num );

rerr rstr_create ( rstr * str, unsigned long cap );
unsigned long rstr_len ( rstr * str );
rerr rstr_reserve ( rstr * str, unsigned long new_cap );
rerr rstr_compact ( rstr * str );
char * rstr_buf ( rstr * dst );
rerr rstr_cat ( rstr * dst, rstr * src );
rerr rstr_set ( rstr * dst, rstr * src );
rerr rstr_cmp ( rstr * a, rstr * b );
rerr rstr_catc ( rstr * str );
rerr rstr_setc ( rstr * str );
rerr rstr_cmpc ( rstr * str );
rerr rstr_repeat ( rstr * str );

rerr rvec_create ( rvec * vec, unsigned long cap );
unsigned long rvec_len ( rvec * vec );
rerr rvec_reserve ( rvec * vec, unsigned long new_cap );
rerr rvec_compact ( rvec * vec );
rerr rvec_concat ( rvec * dst, rvec * src );
rval * rvec_peek ( rvec * vec, unsigned long idx );
rerr rvec_get ( rvec * dst, unsigned long idx, rvec * vec );
rerr rvec_set ( rval * vec, unsigned long idx, rval * item );
rerr rvec_push ( rvec * vec, rval * item );
rerr rvec_pop ( rvec * vec );
rerr rvec_clear ( rvec * vec );

rerr rmap_create ( rmap * map, unsigned long cap );
unsigned long rmap_size ( rmap * map );
rerr rmap_set ( rmap * map, rmap * key, rmap * val );
rval * rmap_peek ( rmap * map, rmap * key );
rerr rmap_get ( rmap * dst, rmap * key, rmap * map );
rerr rmap_unset ( rmap * map, rmap * key );
rerr rmap_keys ( rmap * dst, rmap * map );
rerr rmap_vals ( rmap * dst, rmap * map );
rerr rmap_clear ( rmap * map );

#endif

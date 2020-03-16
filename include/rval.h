#ifndef RILL_RVAL
#define RILL_RVAL

#include "rerr.h"
#include "platform.h"

typedef struct rval rval;
typedef rval ** rmapit;

rerr rval_copy   ( rval * dst, rval * src );
rerr rval_eq     ( rval * val );
rerr rval_clone  ( rval * val );
rerr rval_ref    ( rval * val );
void rval_deref  ( rval ** val );
rerr rval_truthy ( rval * val );
rerr rval_tostr  ( rval * val );

rerr rnum_create ( rval * num );
IXX  rnum_geti   ( rval * num );
rerr rnum_seti   ( rval * num, IXX i );
UXX  rnum_getu   ( rval * num );
rerr rnum_setu   ( rval * num, UXX u );
FXX  rnum_getf   ( rval * num );
rerr rnum_setf   ( rval * num, FXX f );

rval * rstr_create  ( UXX init_cap );
rval * rstr_quick   ( const char * init );
UXX    rstr_len     ( rval * str );
rerr   rstr_reserve ( rval * str, UXX new_cap );
rerr   rstr_compact ( rval * str );
char * rstr_get     ( rval * str );
rerr   rstr_cat     ( rval * dst, rval * src );
rerr   rstr_cpy     ( rval * dst, rval * src );
rerr   rstr_catc    ( rval * dst, const char * src );
rerr   rstr_cpyc    ( rval * str, const char * src );
rerr   rstr_clear   ( rval * str );

rval * rvec_create  ( UXX init_cap );
UXX    rvec_len     ( rval * vec );
rerr   rvec_reserve ( rval * vec, UXX new_cap );
rerr   rvec_compact ( rval * vec );
rerr   rvec_push    ( rval * vec, rval * item );
rerr   rvec_pop     ( rval * vec );
rerr   rvec_get     ( rval * vec, UXX idx );
rerr   rvec_set     ( rval * vec, UXX idx, rval * item );
rerr   rvec_reverse ( rval * vec );
rerr   rvec_clear   ( rval * vec );

rerr   rmap_create ( rval * map );
rerr   rmap_has    ( rval * map, rval * key );
rval * rmap_get    ( rval * map, rval * key );
rval * rmap_keys   ( rval * map );
rval * rmap_vals   ( rval * map );
rerr   rmap_set    ( rval * map, rval * key, rval * item );
rerr   rmap_del    ( rval * map, rval * key );
rmapit rmap_begin  ( rval * map );
rerr   rmap_clear  ( rval * map );

rval * rmapit_key ( rmapit it );
rval * rmapit_val ( rmapit it );
rerr   rmapit_del ( rmapit it );
char   rmapit_ok  ( rmapit it );

#endif

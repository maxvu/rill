#include "rval.h"
#include "rval_impl.h"

rerr rstr_create  ( UXX     cap, rval ** out );
rerr rstr_len     ( rval *  str, UXX  *  out );
rerr rstr_reserve ( rval ** str, UXX     cap );
rerr rstr_compact ( rval ** str );
rerr rstr_cpy     ( rval ** dst, rval *  src );
rerr rstr_cat     ( rval ** dst, rval *  src );
rerr rstr_cmp     ( rval *  a,   rval *  b );
rerr rstr_cpyc    ( rval ** str, char *  src );
rerr rstr_catc    ( rval ** str, char *  src );
rerr rstr_cmpc    ( rval *  str, char *  src );
rerr rstr_repeat  ( rval ** str, UXX     n   );
rerr rstr_clear   ( rval *  str );
rerr rstr_destroy ( rval ** str );

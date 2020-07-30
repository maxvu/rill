#include "rval.h"
#include "rval_impl.h"

rerr rvec_create  ( rval ** vec, UXX     cap );
rerr rvec_len     ( rval *  vec, UXX  *  out );
rerr rvec_reserve ( rval ** vec, UXX     cap );
rerr rvec_compact ( rval ** vec  );
rerr rvec_push    ( rval ** vec, rval *  itm );
rerr rvec_pop     ( rval *  vec, rval ** out );
rerr rvec_get     ( rval *  vec, UXX     idx, rval ** itm );
rerr rvec_set     ( rval *  vec, UXX     idx, rval *  itm );
rerr rvec_shift   ( rval *  vec, rval ** itm );
rerr rvec_unshift ( rval ** vec, rval *  itm );
rerr rvec_reverse ( rval ** vec  );
rerr rvec_clear   ( rval *  vec  );
rerr rvec_destroy ( rval ** vec  );

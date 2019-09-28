#ifndef RILL_RVEC
#define RILL_RVEC

#include "rerr.h"
#include "rval.h"

rerr rvec_init ( rval * val );
rerr rvec_len ( rval * vec );
rerr rvec_reserve ( rval * vec, size_t new_cap );
rerr rvec_compact ( rval * vec );
rval * rvec_get ( rval * vec, size_t index );
rerr   rvec_set ( rval * vec, size_t index, rval * item );
rerr rvec_push ( rval * vec, rval * item );
rerr rvec_pop ( rval * vec );
rerr rvec_shift ( rval * vec );
rerr rvec_unshift ( rval * vec, rval * item );
rval * rvec_head ( rval * vec );
rval * rvec_tail ( rval * vec );
rerr rvec_reverse ( rval * vec );
rerr rvec_concat ( rval * dst, rval * src );
rerr rvec_repeat ( rval * vec );
rerr rvec_clear ( rval * vec );

#endif

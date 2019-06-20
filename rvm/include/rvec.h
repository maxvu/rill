#ifndef RVM_RVEC
#define RVM_RVEC

#include <stddef.h>
#include <stdint.h>

#include "rval.h"

#define RVEC_DEFAULT_SIZE 8
#define RVEC_MINIMUM_SIZE 2
#define RVEC_GROWTH       2.0

typedef struct rvec {
    size_t ref;
    rval * vls;
    size_t len;
    size_t cap;
} rvec;

rval rvecq ( size_t init_cap );
rerr rvec_init ( rval * val, size_t cap );
size_t rvec_len ( rval * val );
rerr rvec_clone ( rval * dst, rval * src );
rerr rvec_reserve ( rval * val, size_t new_cap );
rerr rvec_compact ( rval * val );
rerr rvec_push ( rval * val, rval * item );
rerr rvec_pop ( rval * val );
rval * rvec_peek ( rval * val, size_t index );
rerr rvec_set ( rval * val, size_t index, rval * item );
rerr rvec_get ( rval * dst, size_t index, rval * val );
rerr rvec_fill ( rval * val, rval * item, size_t n );
rerr rvec_reverse ( rval * val );
rerr rvec_concat ( rval * dst, rval * src );
rerr rvec_clear ( rval * val );

#endif

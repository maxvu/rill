#ifndef RILL_RVAL
#define RILL_RVAL

#include "rerr.h"

typedef enum rvtyp {
    RVT_NIL = 0,
    RVT_NUM = 1,
    RVT_STR = 2,
    RVT_VEC = 3,
    RVT_MAP = 4
} rvtyp;

typedef struct rval rval;
typedef struct rval {
    unsigned char rvtyp : 3;
    size_t  tag   : 29;
    size_t  ref;
    union {
        size_t uxx;
        int    ixx;
        double fxx;
        struct {
            size_t len;
            size_t cap;
            char * buf;
        } rstr;
        struct {
            size_t len;
            size_t cap;
            rval * buf;
        } rvec;
        struct {
            size_t occ;
            size_t cap;
            rval * buf;
        } rmap;
    };
} rval;

rvtyp rval_type ( rval * val );
rerr  rval_copy ( rval * dst, rval * src );
rerr  rval_clone ( rval * dst, rval * src );
int   rval_eq ( rval * a, rval * b );
void  rval_ref ( rval * val );
void  rval_deref ( rval * val );
int   rval_contains ( rval * haystack, rval * needle );

rerr ruxx_init ( rval * val );
size_t * ruxx_get ( rval * val );

rerr rixx_init ( rval * val );
int * rixx_get ( rval * val );

rerr rfxx_init ( rval * val );
double * rfxx_get ( rval * fxx );

#endif

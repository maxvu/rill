#ifndef RILL_RVAL_IMPL
#define RILL_RVAL_IMPL

#include <gmp.h>

typedef struct rval {
    unsigned long type : 4;
    unsigned long tag  : 28;
    unsigned long ref;
} rval;

typedef struct rnum {
    rval   nfo;
    mpq_t  mpq;
} rnum;

typedef struct rstr {
    rval          nfo;
    char *        buf;
    unsigned long len;
    unsigned long cap;
} rstr;

typedef struct rvec {
    rval          nfo;
    rval *        vls;
    unsigned long len;
    unsigned long cap;
} rvec;

typedef struct rmap_slot {
    rstr * key;
    rval * val;
} rmap_slot;

typedef struct rmap {
    rval          nfo;
    rmap_slot *   slt;
    unsigned long len;
    unsigned long cap;
} rmap;

double rmap_load ( rval * map );

#endif

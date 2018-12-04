#ifndef RILL_RVAL_RVEC
#define RILL_RVAL_RVEC

#include <stdlib.h>

#define RILL_RVEC_MINSIZE 6
#define RILL_RVEC_DEFAULTSIZE 16
#define RILL_RVEC_GROWTHCOEFF 2.0

typedef struct RRef RRef;

typedef struct RVec {
    RRef * vals;
    size_t len;
    size_t cap;
    size_t refcount;
} RVec;

RVec * __rvec_create ( size_t init_cap );
void __rvec_destroy ( RVec * vec );

void __rvec_lease ( RVec * vec );
void __rvec_release ( RVec * vec );
int __rvec_unique ( RVec * vec );

size_t __rvec_len ( RVec * vec );
int __rvec_reserve ( RVec * vec, size_t new_cap );
int __rvec_compact ( RVec * vec );

RRef * __rvec_get ( RVec * vec, size_t index );
int __rvec_set ( RVec * vec, size_t index, RRef * ref );
int __rvec_push ( RVec * vec, RRef * ref );
int __rvec_pop ( RVec * vec );
int __rvec_concat ( RVec * vec, RVec * other );
int __rvec_fill ( RVec * vec, RRef * val, size_t n );
void __rvec_clear ( RVec * vec );

int __rvec_eq ( RVec * a, RVec * b );

#endif

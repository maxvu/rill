#ifndef RILL_VAL_RVEC
#define RILL_VAL_RVEC

#define RILL_VAL_RVEC_DEFAULTLEN 16
#define RILL_VAL_RVEC_GROWTHCOEF 1.85

#include <stddef.h>

typedef struct RVal RVal;

typedef struct RVec {
    RVal * vals;
    size_t len;
    size_t cap;
    size_t refcount;
} RVec;

/* Construction, destruction */

int rvec_init ( RVec * vec, size_t init_cap );
void rvec_retire ( RVec * vec );
RVec * rvec_create ( size_t init_cap );
void rvec_destroy ( RVec * vec );

/* RVal-generic */

int rvec_contains ( RVec * vec, RVal * val );
int rvec_clone ( RVec * dst, RVec * src );
int rvec_lease ( RVec * vec );
int rvec_release ( RVec * vec );
int rvec_exclude ( RVec * vec );

/* Length and capacity */

int rvec_reserve ( RVec * vec, size_t new_cap );
int rvec_compact ( RVec * vec );
size_t rvec_len ( RVec * vec );

/* Access */

RVal * rvec_get ( RVec * vec, size_t index );
int rvec_push ( RVec * vec, RVal * item );
int rvec_pop ( RVec * vec );
int rvec_clear ( RVec * vec );

#endif

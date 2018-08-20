#include <stddef.h>

#define RILL_VM_RVEC_MIN_SIZE 4
#define RILL_VM_RVEC_GROWTHCOEFF 2.0

typedef struct RVal RVal;

typedef struct RVec {
    RVal * vals;
    size_t len;
    size_t cap;
    size_t refcount;
    RVal * up;
} RVec;

int rvec_init ( RVal * val, size_t init_cap );
void rvec_retire ( RVal * val );
int rvec_reserve ( RVal * val, size_t new_cap );
int rvec_compact ( RVal * val );
int rvec_copy ( RVal * dst, RVal * src );
int rvec_clone ( RVal * dst, RVal * src );
size_t rvec_len ( RVal * val );
RVal * rvec_get ( RVal * val, size_t index );
int rvec_set ( RVal * val, size_t index, const RVal * item );
int rvec_push ( RVal * val, RVal * item );
void rvec_pop ( RVec * vec );
void rvec_clear ( RVec * vec );

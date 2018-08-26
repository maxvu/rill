#ifndef RILL_RVAL_RVEC
#define RILL_RVAL_RVEC

typedef struct RVec {
    RVal * vals;
    size_t len;
    size_t cap;
} RVec;

int __rvec_resize ( RVec * vec );

int rvec_init ( RVec * vec );
size_t rvec_len ( RVec * vec );
int rvec_reserve ( RVec * vec, size_t new_cap );
int rvec_compact ( RVec * vec );
int rvec_get ( RVec * vec, size_t idx );
int rvec_set ( RVec * vec, size_t idx, RVal * item );
int rvec_push ( RVec * vec, RVal * item );
int rvec_pop ( RVec * vec );
int rvec_clear ( RVec * vec );
int rvec_retire ( RVec * vec );

#endif

#ifndef RILL_RVEC
#define RILL_RVEC

#define RILL_RVEC_MINSIZE 6
#define RILL_RVEC_GROWTHFACTOR 1.85

#include <stddef.h>

typedef struct RVec {
    size_t len;
    size_t cap;
    size_t align;
    void * data;
} RVec;

RVec * rvec_create ( size_t init_cap, size_t align );
RVec * rvec_clone ( RVec * original );
int rvec_reserve ( RVec * vec, size_t new_cap );
int rvec_compact ( RVec * vec );
int rvec_push ( RVec * vec, void * item );
void * rvec_get ( RVec * vec, size_t index );
int rvec_set ( RVec * vec, size_t index, void * item );
void rvec_pop ( RVec * vec );
void rvec_clear ( RVec * vec );
int rvec_concat ( RVec * vec, const RVec * other );
size_t rvec_len ( RVec * vec );
size_t rvec_cap ( RVec * vec );
int rvec_is_empty ( RVec * vec );
void rvec_destroy ( RVec * vec );

#endif

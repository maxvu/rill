#ifndef RILL_RVEC
#define RILL_RVEC

#define RILL_RVEC_DEFAULTSIZE  8
#define RILL_RVEC_GROWTHFACTOR 1.85

#include "rmem.h"

#include <stddef.h>
#include <string.h>

typedef struct RVec {
    size_t len;
    size_t cap;
    size_t align;
    char * buf;
} RVec;

RVec * rvec_create ();
int rvec_init ( RVec * vec, size_t align );
RVec * rvec_clone ( RVec * orig );
size_t rvec_len ( RVec * vec );
int rvec_reserve ( RVec * vec, size_t new_cap );
int rvec_compact ( RVec * vec );
void * rvec_get ( RVec * vec, size_t index );
int rvec_set ( RVec * vec, size_t index, void * item );
void * rvec_head ( RVec * vec );
void * rvec_tail ( RVec * vec );
int rvec_push ( RVec * vec, void * item );
void rvec_pop ( RVec * vec );
void rvec_fill ( RVec * vec, size_t n, void * item );
void rvec_clear ( RVec * vec );
void rvec_retire ( RVec * vec );
void rvec_destroy ( RVec * vec );

#endif

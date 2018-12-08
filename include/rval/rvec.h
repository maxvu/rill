#ifndef RILL_RVAL_RVEC
#define RILL_RVAL_RVEC

#include <stdint.h>

#define RILL_RVEC_MINSIZE 2
#define RILL_RVEC_DEFAULTSIZE 16
#define RILL_RVEC_GROWTHCOEFF 2.0

int rvec_init ( size_t init_cap );

size_t rvec_len ( RVal * vec );
size_t rvec_cap ( RVal * vec );
int rvec_reserve ( RVal * vec, size_t new_cap );
int rvec_compact ( RVal * vec );

int rvec_clone ( RVal * dst, RVal * src );
int rvec_eq ( RVal * a, RVal * b );

int rvec_get ( RVal * vec, size_t index );
int rvec_set ( RVal * vec, size_t index, RVal * item );
int rvec_insert ( RVal * vec, size_t index, RVal * item );
int rvec_push ( RVal * vec, RVal * item );
int rvec_pop ( RVal * vec );
int rvec_fill ( RVal * vec, size_t start_index, RVal * item, size_t n );

int rvec_clear ( RVal * vec );

#endif

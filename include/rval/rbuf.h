#ifndef RILL_RVAL_RBUF
#define RILL_RVAL_RBUF

#include "rval/rval.h"

#include <stddef.h>

#define RILL_RBUF_MINCAP 8
#define RILL_RBUF_DEFAULTCAP 24
#define RILL_RBUF_GROWTHFACT 2.25

typedef struct rbuf {
    size_t  ref;
    size_t  len;
    size_t  cap;
    uint8_t bytes[];
} RBuf;

RVal rbuf ( size_t init_cap );
size_t rbuf_len ( RVal * bufval );
int rbuf_reserve ( RVal * bufval, size_t new_cap );
int rbuf_compact ( RVal * bufval );
uint8_t * rbuf_get ( RVal * bufval );
int rbuf_cpy ( RVal * dst, RVal * src );
int rbuf_cat ( RVal * dst, RVal * src );
int rbuf_cmp ( RVal * a, RVal * b );
int rbuf_strcpy ( RVal * bufval, const char * cstr );
int rbuf_strcat ( RVal * bufval, const char * cstr );
int rbuf_strcmp ( RVal * bufval, const char * cstr ); // does not strcmp()
int rbuf_memcpy ( RVal * bufval, const uint8_t * mem, size_t mem_len );
int rbuf_memcat ( RVal * bufval, const uint8_t * mem, size_t mem_len );
int rbuf_memcmp ( RVal * bufval, const uint8_t * mem, size_t mem_len );
int rbuf_repeat ( RVal * bufval, size_t n );
void rbuf_zero ( RVal * bufval );
int rbuf_substr ( RVal * dst_bufval, RVal * src_bufval, size_t start, size_t len );
void rbuf_clear ( RVal * bufval );

#endif

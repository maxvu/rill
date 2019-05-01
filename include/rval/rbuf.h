#ifndef RILL_RVAL_RBUF
#define RILL_RVAL_RBUF

#include "rval/rval.h"

#define RILL_RBUF_MINSIZ 8
#define RILL_RBUF_DEFSIZ 16
#define RILL_RBUF_GROWTH 2.0

typedef struct rbuf {
    size_t    len;
    size_t    cap;
    size_t    ref;
    uint8_t   bts[];
} rbuf;

rval rbufq ();
int rbuf_init ( rval * val, size_t cap );
size_t rbuf_len ( rval * val );
uint8_t * rbuf_get ( rval * bufval );
char * rbuf_strget ( rval * bufval );
int rbuf_reserve ( rval * buf, size_t cap );
int rbuf_compact ( rval * buf );
int rbuf_release ( rval * buf );
int rbuf_exclude ( rval * buf );
int rbuf_memcpy ( rval * buf, uint8_t * mem, size_t mem_len );
int rbuf_memcat ( rval * buf, uint8_t * mem, size_t mem_len );
int rbuf_memcmp ( rval * buf, uint8_t * mem, size_t mem_len );
int rbuf_cpy ( rval * dst, rval * src );
int rbuf_cat ( rval * dst, rval * src );
int rbuf_cmp ( rval * a, rval * b ); // need to check rerr
int rbuf_strcpy ( rval * buf, const char * cstr );
int rbuf_strcat ( rval * buf, const char * cstr );
int rbuf_strcmp ( rval * buf, const char * cstr );
int rbuf_clear ( rval * buf );

#endif

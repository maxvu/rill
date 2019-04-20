#ifndef RILL_RVAL_RBUF
#define RILL_RVAL_RBUF

#include "rval/rval.h"

#define RILL_RBUF_MINSIZ 8
#define RILL_RBUF_DEFSIZ 16
#define RILL_RBUF_GROWTH 2.0

typedef struct RBuf {
    size_t    len;
    size_t    cap;
    size_t    ref;
    uint8_t   bts[];
} RBuf;

RVal rbuf ();
int rbuf_init ( RVal * val, size_t cap );
size_t rbuf_len ( RVal * val );
uint8_t * rbuf_get ( RVal * bufval );
char * rbuf_strget ( RVal * bufval );
int rbuf_reserve ( RVal * buf, size_t cap );
int rbuf_compact ( RVal * buf );
int rbuf_release ( RVal * buf );
int rbuf_exclude ( RVal * buf );
int rbuf_memcpy ( RVal * buf, uint8_t * mem, size_t mem_len );
int rbuf_memcat ( RVal * buf, uint8_t * mem, size_t mem_len );
int rbuf_memcmp ( RVal * buf, uint8_t * mem, size_t mem_len );
int rbuf_cpy ( RVal * dst, RVal * src );
int rbuf_cat ( RVal * dst, RVal * src );
int rbuf_cmp ( RVal * a, RVal * b ); // need to check rerr
int rbuf_strcpy ( RVal * buf, const char * cstr );
int rbuf_strcat ( RVal * buf, const char * cstr );
int rbuf_strcmp ( RVal * buf, const char * cstr );
int rbuf_clear ( RVal * buf );

#endif

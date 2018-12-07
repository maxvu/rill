#ifndef RILL_RVAL_RBUF
#define RILL_RVAL_RBUF

#include <stdint.h>

#define RILL_RBUF_MINSIZE 8
#define RILL_RBUF_GROWTHCOEFF 2.0

int rbuf_init ( size_t init_cap );

size_t rbuf_len ( RVal * buf );
size_t rbuf_cap ( RVal * buf );
int rbuf_reserve ( size_t new_cap );
int rbuf_compact ( RVal * buf );

int rbuf_clone ( RVal * dst, RVal * src );

int rbuf_cpy ( RVal * dst, RVal * src );
int rbuf_cat ( RVal * dst, RVal * src );
int rbuf_cmp ( RVal * a, RVal * b );

int rbuf_cpyc ( RVal * dst, char * cstr );
int rbuf_catc ( RVal * dst, char * cstr );
int rbuf_cmpc ( RVal * dst, char * cstr );

int rbuf_cpyraw ( RVal * dst, uint8_t * raw, size_t raw_len );
int rbuf_catraw ( RVal * dst, uint8_t * raw, size_t raw_len );
int rbuf_cmpraw ( RVal * dst, uint8_t * raw, size_t raw_len );

int rbuf_clear ( RVal * buf );

#endif

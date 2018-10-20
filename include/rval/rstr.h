#ifndef RILL_RVAL_RBUF
#define RILL_RVAL_RBUF

#include <stddef.h>
#include <stdint.h>
#include <string.h>

/*
    Combination byte-buffer / C-string.
    Will ensure null-termination.
*/

typedef struct RVal RVal;

#define RILL_VM_RBUF_MINSIZE 3
#define RILL_VM_RBUF_GROWTHCOEFF 2.0

typedef struct RStr {
    char * buffer;
    size_t refcount;
    size_t len;
    size_t cap;
} RStr;

RStr * __rstr_create ( size_t cap );
int __rstr_resize ( RStr * str, size_t new_cap );
int __rstr_reserve ( RStr * str, size_t new_cap );
int __rstr_cat ( RStr * str, const char * src, size_t len );
void __rstr_destroy ( RStr * str );

int rstr_init ( RVal * val, size_t init_cap );
void rstr_lease ( RVal * val );
void rstr_release ( RVal * val );

int rstr_reserve ( RVal * val, size_t new_cap );
int rstr_compact ( RVal * val );

size_t rstr_len ( RVal * val );
const char * rstr_get ( RVal * val );

int rstr_set ( RVal * dst, RVal * src );
int rstr_cat ( RVal * dst, RVal * src );
int rstr_cmp ( RVal * a, RVal * b );
void rstr_clear ( RVal * val );
int rstr_setc ( RVal * dst, const char * src, size_t src_len );
int rstr_catc ( RVal * dst, const char * src, size_t src_len );
int rstr_cmpc ( RVal * dst, const char * src, size_t src_len );

#endif

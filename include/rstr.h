#ifndef RILL_RSTR
#define RILL_RSTR

#define RILL_RSTR_DEFAULTSIZE 12
#define RILL_RSTR_GROWTHFACTOR 1.75

#include <stddef.h>

typedef struct RStr {
    size_t cap;
    size_t len;
    char * buf;
} RStr;

RStr * rstr_create ();
int rstr_init ( RStr * str );
RStr * rstr_clone ( RStr * orig );
size_t rstr_len ( RStr * str );
int rstr_reserve ( RStr * str, size_t new_cap );
int rstr_compact ( RStr * str );
int rstr_set ( RStr * dst, RStr * src );
int rstr_cat ( RStr * dst, RStr * src );
int rstr_cmp ( RStr * dst, RStr * src );
int rstr_set_cstr ( RStr * dst, const char * src );
int rstr_cat_cstr ( RStr * dst, const char * src );
int rstr_cmp_cstr ( RStr * dst, const char * src );
void rstr_retire ( RStr * str );
void rstr_destroy ( RStr * str );

#endif

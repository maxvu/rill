#ifndef RILL_VM_RSTR
#define RILL_VM_RSTR

#include <stddef.h>

#include "rval.h"

#define RILL_VM_RSTR_MINSIZE 8
#define RILL_VM_RSTR_GROWTHCOEFF 1.6

typedef struct RStr {
    char * buf;
    size_t len;
    size_t cap;
    size_t refcount;
} RStr;

int rstr_init ( RVal * val, size_t init_cap );
void rstr_retire ( RVal * val );
int rstr_reserve ( RVal * val, size_t new_cap );
int rstr_compact ( RVal * val );
size_t rstr_len ( RVal * val );
const char * rstr_cstr ( RVal * val );
int rstr_set ( RVal * val, RVal * other );
int rstr_cat ( RVal * val, RVal * other );
int rstr_cmp ( RVal * val, RVal * other );
int rstr_setc ( RVal * val, const char * cstr );
int rstr_catc ( RVal * val, const char * cstr );
int rstr_cmpc ( RVal * val, const char * cstr );
int rstr_clear ( RVal * val );

#endif

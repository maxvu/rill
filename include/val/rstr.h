#ifndef RILL_VAL_RSTR
#define RILL_VAL_RSTR

#define RILL_VAL_RSTR_DEFAULTLEN 16
#define RILL_VAL_RSTR_GROWTHCOEF 1.6

#include <stddef.h>

typedef struct RStr {
    char * buf;
    size_t len;
    size_t cap;
    size_t refcount;
} RStr;

/* Construction, destruction */

// Prepare an already-allocated RStr.
int rstr_init ( RStr * str, size_t init_cap );

// Free an RStr's underlying buffer.
void rstr_retire ( RStr * str );

// Allocate and prepare an RStr.
RStr * rstr_create ( size_t init_cap );

// Deallocate an RStr.
void rstr_destroy ( RStr * str );

/* RVal-generic */

int rstr_lease ( RStr * str );
int rstr_release ( RStr * str );
int rstr_exclude ( RStr * str );

/* Length and capacity */

int rstr_reserve ( RStr * str, size_t new_cap );
int rstr_compact ( RStr * str );
size_t rstr_len ( RStr * str );

/* Raw access */

const char * rstr_cstr ( RStr * str );

/* Access */

int rstr_set ( RStr * str, const RStr * other );
int rstr_cat ( RStr * str, const RStr * other );
int rstr_cmp ( RStr * str, const RStr * other );

/* C-string access */

int rstr_setc ( RStr * str, const char * cstr );
int rstr_catc ( RStr * str, const char * cstr );
int rstr_cmpc ( RStr * str, const char * cstr );

#endif

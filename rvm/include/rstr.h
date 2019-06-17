#ifndef RVM_RSTR
#define RVM_RSTR

#include "rval.h"

#include <stddef.h>
#include <stdint.h>

typedef unsigned int rerr;
typedef struct rval rval;

#define RSTR_MINIMUM_SIZE 5
#define RSTR_GROWTH       1.6

typedef struct rstr {
    size_t ref;
    char * buf;
    size_t len;
    size_t cap;
} rstr;

rval rstrq ( const char * cstr );
rerr rstr_init ( rval * val, size_t cap );
size_t rstr_len ( rval * val );
char * rstr_buf ( rval * val );

rerr rstr_reserve ( rval * val, size_t new_cap );
rerr rstr_compact ( rval * val );

rerr rstr_cpy ( rval * dst, rval * src );
rerr rstr_cat ( rval * dst, rval * src );
int rstr_cmp ( rval * a, rval * b );

rerr rstr_mcpy ( rval * val, uint8_t * mem, size_t mem_len );
rerr rstr_mcat ( rval * val, uint8_t * mem, size_t mem_len );
int rstr_mcmp ( rval * val, uint8_t * mem, size_t mem_len );

rerr rstr_qcpy ( rval * val, const char * cstr );
rerr rstr_qcat ( rval * val, const char * cstr );
int rstr_qcmp ( rval * val, const char * cstr );

rerr rstr_clear ( rval * val );

#endif

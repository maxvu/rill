#ifndef RILL_RLEXIT
#define RILL_RLEXIT

#include "util/rutf8it.h"
#include "rval/rval.h"

#include <stddef.h>

typedef struct rlexit {
    rutf8it uit; // UTF-8 iterator
    size_t  lno; // line number
    size_t  lps; // position (by codepoint) within line
} rlexit;

int rlexit_init ( rlexit * it, uint8_t * begin, uint8_t * end );
int rlexit_copy ( rlexit * dst, rlexit * src );
int rlexit_retire ( rlexit * it );

int rlexit_step ( rlexit * it );

int rlexit_cdpt ( rlexit * it );
uint8_t * rlexit_text ( rlexit * it );
size_t rlexit_pos ( rlexit * it );
size_t rlexit_lineno ( rlexit * it );
int rlexit_linepos ( rlexit * it );
int rlexit_err ( rlexit * it );
int rlexit_ok ( rlexit * it );
int rlexit_eof ( rlexit * it );
int rlexit_done ( rlexit * it );

int rlexit_range ( rval * token, rlexit * begin, rlexit * end, int type );

#endif

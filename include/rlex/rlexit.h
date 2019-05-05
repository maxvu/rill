#ifndef RILL_RLEXIT
#define RILL_RLEXIT

#include "util/rutf8it.h"

typedef struct rlexit {
    rutf8it uit;
    size_t line;
    size_t offset;
} rlexit;

int rlexit_init ( rlexit * it, uint8_t * begin, uint8_t * end );
int rlexit_copy ( rlexit * dst, rlexit * src );

int rlexit_step ( rlexit * it );

int rlexit_ok ( rlexit * it );
int rlexit_done ( rlexit * it );
int rlexit_cdpt ( rlexit * it );
uint8_t * rlexit_pos ( rlexit * it );

size_t rlexit_line ( rlexit * it );
size_t rlexit_offset ( rlexit * it );

#endif

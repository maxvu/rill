#ifndef RILL_UTF8IT
#define RILL_UTF8IT

#include "util/rutf8.h"

#include <stdint.h>
#include <stddef.h>

typedef struct rutf8it {
    size_t    pos;  // index of current codepoint in stream
    uint8_t * cur;  // pointer to byte of next codepoint
    uint8_t * end;  // end of stream
    rutf8peek peek; // result of decode
    uint8_t   err;  // status
} rutf8it;

int rutf8it_init ( rutf8it * it, uint8_t * begin, uint8_t * end );
int rutf8it_copy ( rutf8it * dst, rutf8it * src );
int rutf8it_step ( rutf8it * it );
int rutf8it_err ( rutf8it * it );
int rutf8it_ok ( rutf8it * it );
int rutf8it_eof ( rutf8it * it );
int rutf8it_done ( rutf8it * it );
uint8_t * rutf8it_pos ( rutf8it * it );
int rutf8it_cdpt ( rutf8it * it );
int rutf8it_nbytes ( rutf8it * it );

#endif

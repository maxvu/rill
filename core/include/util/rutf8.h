#ifndef RILL_UTF8
#define RILL_UTF8

#include <stdint.h>
#include <stddef.h>

typedef struct RUTF8Peek {
    uint8_t n_bytes;
    unsigned int codepoint;
} RUTF8Peek;

int rutf8_peek ( RUTF8Peek * peek, uint8_t * pos, uint8_t * end );
int rutf8_scan ( size_t * length, uint8_t * pos, uint8_t * end );

#endif

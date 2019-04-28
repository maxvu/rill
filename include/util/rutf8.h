#ifndef RILL_UTF8
#define RILL_UTF8

#include <stdint.h>
#include <stddef.h>

/*
    decoding status
*/
#define RILL_ERR_UTFOK          0x00
#define RILL_ERR_UTF8EOFTRUNC   0x01
#define RILL_ERR_UTF8EARLYTRUNC 0x02
#define RILL_ERR_UTF8INVALIDBYT 0x03

typedef struct rutf8peek {
    uint8_t n_bytes;
    unsigned int codepoint;
} rutf8peek;

int rutf8_peek ( rutf8peek * peek, uint8_t * pos, uint8_t * end );
int rutf8_scan ( size_t * length, uint8_t * pos, uint8_t * end );

#endif

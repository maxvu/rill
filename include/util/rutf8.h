#ifndef RILL_UTF8
#define RILL_UTF8

#include <stdint.h>
#include <stddef.h>

typedef enum RUTF8ScanStatus {
    RUTF8_OK,
    RUTF8_PASSED_NULLPTR,
    RUTF8_EOF_TRUNCATION,
    RUTF8_EARLY_TRUNCATION,
    RUTF8_INVALID_BYTE
} RUTF8ScanStatus;

typedef struct RUTF8Peek {
    uint8_t n_bytes;
    RUTF8ScanStatus error;
    unsigned int codepoint;
} RUTF8Peek;

typedef struct RUTF8Scan {
    size_t length;
    RUTF8ScanStatus error;
} RUTF8Scan;

int rutf8_peek ( RUTF8Peek * peek, uint8_t * pos, uint8_t * end );
int rutf8_scan ( RUTF8Scan * scan, uint8_t * pos, uint8_t * end );

#endif

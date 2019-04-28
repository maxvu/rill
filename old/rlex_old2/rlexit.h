#ifndef RILL_RLEXIT
#define RILL_RLEXIT

#include "util/rutf8.h"
#include "rval/rval.h"

#include <stddef.h>

#define RILL_LEXIT_DEFAULT_BUFFER_SIZE 64

#define RILL_LEXIT_OK                    1
#define RILL_LEXIT_UNEXPECTED_CHAR       2
#define RILL_LEXIT_UNCLOSED_STRING       3
#define RILL_LEXIT_INVALID_STRING_ESCAPE 4
#define RILL_LEXIT_INVALID_UTF8          5
#define RILL_LEXIT_UNDERLYING_ERROR      6

typedef struct rlexiter {
    struct {
        size_t num;
        size_t pos;
    } line;
    size_t pos;
    RUTF8Peek peek;
    struct {
        uint8_t *    bytes; // buffer
           // position in buffer
        size_t       len;   // buffer length
        RUTF8Peek    peek;  // current UTF-8 codepoint
    } buffer;
} rlexit;

unsigned int err;       // status code
rval         result;    // rvec of rlextok's

typedef struct rlexit {
    size_t       line;      // line number
    size_t       pos;       // position in line
    struct {
        uint8_t *    bytes; // buffer
        size_t       pos;   // position in buffer
        size_t       len;   // buffer length
        RUTF8Peek    peek;  // current UTF-8 codepoint
    } buffer;
    unsigned int err;       // status code
    rval         result;    // rvec of rlextok's
} rlexit;

int rlexit_init ( rlexit * it, rval * buf );
int rlexit_retire ( rlexit * it );

unsigned int rlexit_geterr ( rlexit * it );
int rlexit_seterr ( rlexit * it, unsigned int err );

uint8_t * rlexit_buf ( rlexit * it );
int rlexit_ok ( rlexit * it );
int rlexit_eof ( rlexit * it );
int rlexit_done ( rlexit * it );

int rlexit_step ( rlexit * it );
int rlexit_peek ( rlexit * it );

int rlexit_clip ( rlexit * it, uint8_t * from, uint8_t type );
int rlexit_clipchar ( rlexit * it, uint8_t type );
int rlexit_add ( rlexit * it, rval * str, uint8_t type );
int rlexit_addchar ( rlexit * it, int chr, uint8_t type );

#endif

#ifndef RILL_RLEXSTT
#define RILL_RLEXSTT

#include "util/rutf8.h"
#include "rval/rval.h"

#include <stddef.h>

#define RILL_LEXSTT_DEFAULT_BUFFER_SIZE 64

#define RILL_LEXSTT_OK                    1
#define RILL_LEXSTT_UNEXPECTED_CHAR       2
#define RILL_LEXSTT_UNCLOSED_STRING       3
#define RILL_LEXSTT_INVALID_STRING_ESCAPE 4
#define RILL_LEXSTT_UNDERLYING_ERROR      5

typedef struct rlexstt {
    size_t       line;      // line number
    size_t       line_pos;  // position in line
    uint8_t *    buf;       // buffer
    size_t       buf_len;   // buffer length
    size_t       pos;       // position in buffer
    unsigned int err;       // status code
    RUTF8Peek    peek;      // UTF-8 cursor result
    rval         result;    // rvec of rlextok's
} rlexstt;

int rlexstt_init ( rlexstt * stt, rval * buf );
int rlexstt_retire ( rlexstt * stt );

uint8_t * rlexstt_pos ( rlexstt * stt );
int rlexstt_ok ( rlexstt * stt );
int rlexstt_eof ( rlexstt * stt );
int rlexstt_done ( rlexstt * stt );

int rlexstt_step ( rlexstt * stt );
int rlexstt_peek ( rlexstt * stt );
int rlexstt_add ( rlexstt * stt, uint8_t * begin, uint8_t type );
int rlexstt_addstr ( rlexstt * stt, rval * str, uint8_t type );

#endif
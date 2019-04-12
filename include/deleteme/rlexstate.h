#include "rval/rval.h"
#include "util/rutf8.h"

#include <stddef.h>

#define RILL_LEXSTATE_RESULT_BUFFER_SIZE 64

typedef struct rlexstate {
    size_t line;          // line number
    size_t line_pos;      // position in line
    size_t pos;           // position in buffer
    unsigned int err;     // status code
    RUTF8Peek peek;       // UTF-8 cursor result
    uint8_t * buf;        // buffer begin
    uint8_t * buf_end;    // buffer end
    RVal result;          // rvec of rlextok's
} rlexstate;

int rlexstate_init ( rlexstate * state, RVal * buf );
void rlexstate_retire ( rlexstate * state );
int rlexstate_step ( rlexstate * state );
int rlexstate_peek ( rlexstate * state );
uint8_t * rlexstate_pos ( rlexstate * state );
int rlexstate_eof ( rlexstate * state );
int rlexstate_ok ( rlexstate * state );
int rlexstate_add_token ( rlexstate * state, uint8_t * begin, uint8_t type );
#ifndef RILL_RLEXSTT
#define RILL_RLEXSTT

#include "rlex/rlexit.h"
#include "rval/rval.h"
#include "util/rutf8it.h"

#define RILL_LEX_OK                    1
#define RILL_LEX_UNEXPECTED_CHAR       2
#define RILL_LEX_UNCLOSED_STRING       3
#define RILL_LEX_UNCLOSED_COMMENT      4
#define RILL_LEX_INVALID_UTF8          5
#define RILL_LEX_UNDERLYING_ERROR      6

typedef struct rlexstt {
    rlexit begin;
    rlexit end;
    rval tokens;
    int status;
} rlexstt;

int rlexstt_init ( rlexstt * stt, uint8_t * begin, uint8_t * end );
int rlexstt_retire ( rlexstt * stt );

int rlexstt_step ( rlexstt * stt );
int rlexstt_range ( rlexstt * stt, int type );

int rlexstt_ok ( rlexstt * stt );
int rlexstt_err ( rlexstt * stt );
int rlexstt_done ( rlexstt * stt );
int rlexstt_cdpt ( rlexstt * stt );

int rlexstt_tokens ( rval * dst, rlexstt * stt );

#endif

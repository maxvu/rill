#ifndef RILL_RLEXTOK
#define RILL_RLEXTOK

#include "config/arch.h"

/*
    [
        type
        text (source)
        start line
        start pos
    ]
*/

typedef struct rval rval;

int rlextok (
    rval * tok,
    unsigned int type,
    RILL_UXX_TYPE line,
    RILL_UXX_TYPE pos,
    rval * text
);

int rlextok_type ( rval * token );
rval * rlextok_line ( rval * token );
rval * rlextok_pos  ( rval * token );
rval * rlextok_text  ( rval * token );

int rlextok_dump  ( rval * token );

#endif

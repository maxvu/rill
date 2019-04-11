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

typedef struct RVal RVal;

int rlextok (
    RVal * tok,
    unsigned int type,
    RILL_UXX_TYPE line,
    RILL_UXX_TYPE pos,
    RVal * text
);

RVal * rlextok_type ( RVal * token );
RVal * rlextok_line ( RVal * token );
RVal * rlextok_pos  ( RVal * token );
RVal * rlextok_text  ( RVal * token );

RVal * rlextok_dump  ( RVal * token );

#endif

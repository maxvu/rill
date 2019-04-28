#ifndef RILL_RLEXTOK
#define RILL_RLEXTOK

#include "config/arch.h"
#include "rval/rval.h"

/*
    [ type, text (source), start line, start pos ]
*/

int rlextok (
    RVal * tok,
    unsigned int type,
    RILL_UXX_TYPE line,
    RILL_UXX_TYPE pos,
    RVal * text
);

int rlextok_type ( RVal * token );
RVal * rlextok_line ( RVal * token );
RVal * rlextok_pos  ( RVal * token );
RVal * rlextok_text  ( RVal * token );

int rlextok_dump  ( RVal * token );

#endif

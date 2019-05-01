#ifndef RILL_RLEXTOK
#define RILL_RLEXTOK

#include "config/arch.h"
#include "rval/rval.h"

#define RILL_LEXTOK_WHITESPACE      1
#define RILL_LEXTOK_IDENTIFIER      2
#define RILL_LEXTOK_NUMBER          3
#define RILL_LEXTOK_STRING          4
#define RILL_LEXTOK_COMMENT         5
#define RILL_LEXTOK_STRUCT_OPEN     6
#define RILL_LEXTOK_STRUCT_CLOSE    7
#define RILL_LEXTOK_QUOTE_OPEN      8
#define RILL_LEXTOK_QUOTE_CLOSE     9
#define RILL_LEXTOK_COMPILE_OPEN   10
#define RILL_LEXTOK_COMPILE_CLOSE  11

/*
    [ type, text (source), start line, start pos ]
*/

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

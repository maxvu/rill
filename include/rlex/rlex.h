#ifndef RILL_RLEX
#define RILL_RLEX

#include "rval/rval.h"
#include "util/rutf8.h"

/*
    [ unit_name, line, pos, last_run ]
*/

RVal rlexer ( RVal * unit_name );
int rlexer_lex ( RVal * lexer );
int rlexer_tokens ( RVal * lexer );

/*
    [
        text (source)
        start line
        start pos
    ]
*/

RVal * rlexer_token_type ( RVal * token );
RVal * rlexer_token_line ( RVal * token );
RVal * rlexer_token_pos  ( RVal * token );
RVal * rlexer_token_text  ( RVal * token );

#endif

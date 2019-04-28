#ifndef RILL_RLEX_RLEX
#define RILL_RLEX_RLEX

#include "config/arch.h"
#include "rlex/rlexit.h"

#define RILL_LEXTOK_WHITESPACE      1
#define RILL_LEXTOK_IDENTIFIER      2
#define RILL_LEXTOK_NUMBER          3
#define RILL_LEXTOK_COMMENT         4
#define RILL_LEXTOK_STRING          6
#define RILL_LEXTOK_HASH_OPEN       7
#define RILL_LEXTOK_HASH_CLOSE      8
#define RILL_LEXTOK_LIST_OPEN       9
#define RILL_LEXTOK_LIST_CLOSE     10
#define RILL_LEXTOK_QUOTE_OPEN     11
#define RILL_LEXTOK_QUOTE_CLOSE    12
#define RILL_LEXTOK_COMPILE_OPEN   13
#define RILL_LEXTOK_COMPILE_CLOSE  14

int rlex ( rval * dst, rval * lexbuf );
int rlex_dump ( rval * lexbuf );

#endif

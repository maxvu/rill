#ifndef RILL_LEX
#define RILL_LEX

#include "rlex/rlexstt.h"
#include "rval/rval.h"

int rlex ( rlexstt * stt, uint8_t * begin, uint8_t * end );
void rlex_dump ( rval * result );

#endif

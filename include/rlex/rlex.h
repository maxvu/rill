#ifndef RILL_LEX_RLEX
#define RILL_LEX_RLEX

#include "util/rutf8it.h"

#define RILL_LEX_DEFAULT_BUFFER_SIZE 64

#define RILL_LEX_OK                    1
#define RILL_LEX_UNEXPECTED_CHAR       2
#define RILL_LEX_UNCLOSED_STRING       3
#define RILL_LEX_UNCLOSED_COMMENT      4
#define RILL_LEX_INVALID_UTF8          5
#define RILL_LEX_UNDERLYING_ERROR      6

typedef struct rval rval;

int rlex ( rval * result, rutf8it * it, int * status );

#endif

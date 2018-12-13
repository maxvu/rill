#ifndef RILL_CONFIG
#define RILL_CONFIG

#include <stdint.h>

#define RILL_ALLOC(N) malloc(N)
#define RILL_REALLOC(X, N) realloc(X, N)
#define RILL_DEALLOC(X) free(X)

#define RILL_UXX_TYPE uint64_t
#define RILL_UXX_MAX  UINT64_MAX

#define RILL_IXX_TYPE int64_t
#define RILL_FXX_TYPE double

#endif

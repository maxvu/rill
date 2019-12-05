#ifndef RILL_RVAL
#define RILL_RVAL

#include <stdint.h>

#ifdef RILL_32BIT
    #define IXX int32_t;
    #define UXX uint32_t;
    #define FXX float;

    #define IXX_MAX INT32_MAX
    #define UXX_MAX UINT32_MAX
#else
    #define IXX int64_t;
    #define UXX uint64_t;
    #define FXX double;

    #define IXX_MAX INT64_MAX
    #define UXX_MAX UINT64_MAX
#endif

rerr rval_type
rerr rval_copy
rerr rval_clone
char rval_cycles
rerr rval_compact
rerr rval_exclude
char rval_eq
rerr rval_ref
rerr rval_deref

#endif

#ifndef RILL_COMMON
#define RILL_COMMON

#ifdef RILL_32BIT
    typedef int32_t  ixx_t;
    typedef uint32_t uxx_t;
    typedef double   fxx_t;
#endif

#ifdef RILL_64BIT
    typedef int64_t  ixx_t;
    typedef uint64_t uxx_t;
    typedef double   fxx_t;
#endif

#define RERR_OK        0
#define RERR_USE_ARG   64
#define RERR_SYS_ALLOC 128

typedef unsigned int rerr;

#endif

#ifndef RILL_PLATFORM
#define RILL_PLATFORM

#ifdef RILL_32BIT
    typedef int32_t  ixx_t;
    typedef uint32_t uxx_t;
#endif

#ifdef RILL_64BIT
    typedef int64_t  ixx_t;
    typedef uint64_t uxx_t;
#endif

#endif

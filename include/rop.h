#ifndef RILL_BYTECODE
#define RILL_BYTECODE

#include <stdint.h>

#ifndef RILL_WORDSIZE
    #error Must provide RILL_WORDSIZE on compilation.
#endif

typedef enum ROpList {
    ROP_NOP,
    ROP_LOAD,
} ROpList;

#if RILL_WORDSIZE == 64
    typedef union {
        uint8_t  ops[8];
        uint64_t value;
    } ROp;
#elif RILL_WORDSIZE == 32
    typedef union {
        uint8_t  ops[4];
        uint32_t value;
    } ROp;
#else
    #error Unsupported RILL_WORDSIZE.
#endif

#endif

#ifndef RILL_RVAL_RREF
#define RILL_RVAL_RREF

#include <stdint.h>

#include "environment.h"

typedef enum RValType {
    NIL = 0,
    UXX = 1,
    IXX = 2,
    FXX = 3,
    BUF = 32,
    VEC = 64,
    MAP = 128
} RValType;

typedef struct RBuf RBuf;
typedef struct RVec RVec;
typedef struct RMap RMap;

#ifdef RILL_32BIT
    typedef struct RRef {
        RValType type;
        union {
            uint32_t uxx;
            int32_t  ixx;
            double   fxx;
            RBuf *   buf;
            RVec *   vec;
            RMap *   map;
        };
    } RVal;
#else
    typedef struct RRef {
        RValType type;
        union {
            uint64_t uxx;
            int64_t  ixx;
            double   fxx;
            RBuf *   buf;
            RVec *   vec;
            RMap *   map;
        };
    } RVal;
#endif

RRef rref_nil ();

RValType rref_type ( RRef * ref );
int rref_isfw ( RRef * ref );

void rref_copy ( RRef * dst, RRef * src );
void rref_move ( RRef * dst, RRef * src );
void rref_swap ( RRef * a, RRef * b );
int rref_clone ( RRef * dst, RRef * src );
int rref_contains ( RRef * haystack, RRef * needle );
int rref_exclude ( RRef * dst, RRef * src );
void rref_lease ( RRef * val );
void rref_release ( RRef * val );
int rref_eq ( RRef * dst, RRef * src );

#endif

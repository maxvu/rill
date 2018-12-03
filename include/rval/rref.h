#ifndef RILL_RVAL_RREF
#define RILL_RVAL_RREF

#include <stdint.h>

#include "environment.h"

typedef enum RValType {
    RVT_NIL = 0,
    RVT_UXX = 1,
    RVT_IXX = 2,
    RVT_FXX = 3,
    RVT_BUF = 32,
    RVT_VEC = 64,
    RVT_MAP = 128
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

void rref_ref ( RRef * val );
void rref_deref ( RRef * val );

int rref_eq ( RRef * a, RRef * b );
void rref_dump ( RRef * val );

#endif

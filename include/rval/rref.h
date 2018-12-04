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

typedef struct RRef {
    RValType type;
    union {
        RILL_UXX_TYPE uxx;
        RILL_IXX_TYPE ixx;
        RILL_FXX_TYPE fxx;
        RBuf *        buf;
        RVec *        vec;
        RMap *        map;
    };
} RRef;

RRef rref_nil ();
RRef rref_uxx ( RILL_UXX_TYPE u );
RRef rref_ixx ( RILL_IXX_TYPE i );
RRef rref_fxx ( RILL_FXX_TYPE f );

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
int rref_eq ( RRef * a, RRef * b );
void rref_dump ( RRef * val );

#endif

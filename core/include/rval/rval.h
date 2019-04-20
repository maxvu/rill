#ifndef RILL_RVAL_RVAL
#define RILL_RVAL_RVAL

#include "config/arch.h"

#include <stddef.h>
#include <stdint.h>

/*
    The following invariants must hold:
        - All null-pointer arguments should be immediately rejected.
        - Except _init() functions, and fixed-width _set()'s, invocations on
          arguments on wrong-typed values should be rejected.
        - Recursive values (i.e. RVec's and RMap's) must check - before
          accepting a new member value - that it does not eventually _cycleto()
          itself. If it does, _exclude() must be called on the container.
        - Convenience inner-pointers (e.g. `RVec vec = vecval->vec`) must be
          invalidated whenever a reallocation happens (e.g. _exclude(),
          _reserve()).
        - Whenever a mutating function fails, it must leave the operand value
          in a valid state. (CTRL+F for an `RVal tmp;` pattern.)
*/

typedef enum RValType RValType;
typedef struct RVal RVal;
typedef struct RBuf RBuf;
typedef struct RVec RVec;
typedef struct RMap RMap;
typedef struct RMapSlot RMapSlot;

enum RValType {
    RVT_NIL = 0, // non-value
    RVT_IXX = 1, // signed integer
    RVT_UXX = 2, // unsigned integer
    RVT_FXX = 3, // floating-point
    RVT_VDP = 4, // void pointer
    RVT_BUF = 5, // buffer
    RVT_VEC = 6, // vector
    RVT_MAP = 7  // map
};

struct RVal {
    RValType typ;
    union {
        RILL_IXX_TYPE ixx;
        RILL_UXX_TYPE uxx;
        RILL_FXX_TYPE fxx;
        void *        vdp;
        RBuf *        buf;
        RVec *        vec;
        RMap *        map;
    };
};

int rval_type ( RVal * val );
int rval_lease ( RVal * val );
int rval_release ( RVal * val );
int rval_exclude ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
int rval_clone ( RVal * dst, RVal * src );
int rval_move ( RVal * dst, RVal * src );
int rval_swap ( RVal * a, RVal * b );
int rval_eq ( RVal * a, RVal * b );
int rval_truthy ( RVal * val );
int rval_isnil ( RVal * val );
int rval_cyclesto ( RVal * haystack, RVal * needle );
int rval_pack ( RVal * bytes, RVal * val );
int rval_unpack ( RVal * val, RVal * bytes );
void rval_dump ( RVal * val );

RVal rnil ();

#endif

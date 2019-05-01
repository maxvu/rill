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
        - Recursive values (i.e. rvec's and rmap's) must check - before
          accepting a new member value - that it does not eventually _cycleto()
          itself. If it does, _exclude() must be called on the container.
        - Convenience inner-pointers (e.g. `rvec vec = vecval->vec`) must be
          invalidated whenever a reallocation happens (e.g. _exclude(),
          _reserve()).
        - Whenever a mutating function fails, it must leave the operand value
          in a valid state. (CTRL+F for an `rval tmp;` pattern.)
*/

typedef enum rvalType rvalType;
typedef struct rval rval;
typedef struct rbuf rbuf;
typedef struct rvec rvec;
typedef struct rmap rmap;
typedef struct rmapSlot rmapSlot;

enum rvalType {
    RVT_NIL = 0, // non-value
    RVT_IXX = 1, // signed integer
    RVT_UXX = 2, // unsigned integer
    RVT_FXX = 3, // floating-point
    RVT_VDP = 4, // void pointer
    RVT_BUF = 5, // buffer
    RVT_VEC = 6, // vector
    RVT_MAP = 7  // map
};

struct rval {
    rvalType typ;
    union {
        RILL_IXX_TYPE ixx;
        RILL_UXX_TYPE uxx;
        RILL_FXX_TYPE fxx;
        void *        vdp;
        rbuf *        buf;
        rvec *        vec;
        rmap *        map;
    };
};

int rval_type ( rval * val );
int rval_lease ( rval * val );
int rval_release ( rval * val );
int rval_exclude ( rval * val );
int rval_copy ( rval * dst, rval * src );
int rval_clone ( rval * dst, rval * src );
int rval_move ( rval * dst, rval * src );
int rval_swap ( rval * a, rval * b );
int rval_eq ( rval * a, rval * b );
int rval_truthy ( rval * val );
int rval_isnil ( rval * val );
int rval_cyclesto ( rval * haystack, rval * needle );
int rval_pack ( rval * bytes, rval * val );
int rval_unpack ( rval * val, rval * bytes );
void rval_dump ( rval * val );

rval rnil ();

#endif

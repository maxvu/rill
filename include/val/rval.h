#ifndef RILL_VAL_RVAL
#define RILL_VAL_RVAL

#include <stdio.h>
#include <stddef.h>

typedef struct RStr RStr;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef enum RValType {
    NIL = 0,
    UXX = 1,
    IXX = 2,
    DBL = 3,
    STR = 4,
    VEC = 5,
    MAP = 6
} RValType;

typedef struct RVal {
    RValType type;
    union {
        size_t      uxx;
        signed long ixx;
        double      dbl;
        RStr *      str;
        RVec *      vec;
        RMap *      map;
    };
} RVal;

// Discard recursive structures and set to NIL.
int rval_retire ( RVal * val );

// Determine type.
RValType rval_type ( RVal * val );

// Determine whether a certain recursive structure contains another.
int rval_contains ( RVal * haystack, RVal * needle );

// Set the value of one RVal to another's.
int rval_copy ( RVal * dst, RVal * src );

// Deep copy one RVal into another.
int rval_clone ( RVal * dst, RVal * src );

// Manually increment refcount.
void rval_lease ( RVal * val );

// Decrement refcount and perhaps destroy.
void rval_release ( RVal * val );

// Clone in-place.
int rval_exclude ( RVal * val );

#endif

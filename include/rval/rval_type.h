#ifndef RILL_RVAL_RVALTYPE
#define RILL_RVAL_RVALTYPE

typedef enum RValType {
    NIL = 0,
    UXX = 1,
    IXX = 2,
    FXX = 3,
    BUF = 4,
    VEC = 5,
    MAP = 6
} RValType;

#endif

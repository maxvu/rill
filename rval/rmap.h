#ifndef RILL_RVAL_RMAP
#define RILL_RVAL_RMAP

typedef struct RCtx RCtx;
typedef struct RVal RVal;
typedef struct RBuf RBuf;

/*
    Hash table.
*/

typedef struct RMapSlot {
    RVal * key;
    RVal * val;
} RMapSlot;

typedef struct RMap {
    RMapSlot * slots;
    size_t len;
    size_t cap;
} RMap;

#endif

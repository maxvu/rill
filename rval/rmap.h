#ifndef RILL_RVAL_RMAP
#define RILL_RVAL_RMAP

/*
    Simple hash-table.
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

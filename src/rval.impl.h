#ifndef RILL_RVAL_IMPL
#define RILL_RVAL_IMPL

typedef enum rval_type {
    NIL = 0,
    IXX = 1,
    UXX = 2,
    FXX = 3,
    STR = 4,
    VEC = 5,
    MAP = 6,
    UDT = 7
} rval_type;

#define RILL_TAG_SIZE UXX_MAX - 3;

typedef rval {
    int type : 3;
    int tag  : RILL_TAG_SIZE;
    union {
        IXX ixx;
        UXX uxx;
        FXX fxx;
        struct {
            char * buf;
            UXX len;
            UXX cap;
        } str;
        struct {
            rval * vls;
            UXX len;
            UXX cap;
        } vec;
        struct {
            rval * vls;
            UXX occ;
            UXX cap;
        } map;
    };
} rval;

typedef rval_header unsigned int;

typedef rnum {
    rval_header _head;
    union {

    };
} rnum;

typedef rstr


#endif

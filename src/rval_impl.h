#ifndef RILL_RVAL_IMPL
#define RILL_RVAL_IMPL

#include "platform.h"

typedef struct rval {
    UXX type : 8;
    UXX tag  : RVAL_TAG_SIZE;
    UXX ref  : RVAL_REF_SIZE;
    union {
        IXX ixx;
        UXX uxx;
        FXX fxx;
        struct {
            const char * buf;
            UXX len;
            UXX cap;
        } str;
        struct {
            rval * vls;
            UXX    len;
            UXX    cap;
        } vec;
        struct {
            rval * vls;
            UXX    occ;
            UXX    cap;
        } map;
    };
} rval;

// typedef struct rnum {
//     UXX head;
//     union {
//         IXX i;
//         UXX u;
//         FXX f;
//     };
// } rnum;
//
// typedef struct rstr {
//     UXX head;
//     const char *
//     UXX len;
//     UXX cap;
// };

#endif

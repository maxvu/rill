#ifndef RILL_VM_RVAL
#define RILL_VM_RVAL

#include <stddef.h>

enum RValType {
    NIL = 0,
    UXX = 1,
    IXX = 2,
    DBL = 3,
    STR = 4,
    VEC = 5,
    MAP = 10
};

typedef struct RStr RStr;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef struct RVal {
    enum RValType type;
    union {
        unsigned long uxx;
        signed long   ixx;
        double        dbl;
        RStr *        str;
        RVec *        vec;
        RMap *        map;
        void *        udo;
    };
} RVal;

void rval_zero ( RVal * val );
enum RValType rval_type ( RVal * val );
int rval_lease ( RVal * val );
void rval_clear ( RVal * val );
int rval_compact ( RVal * val );
int rval_exclude ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
int rval_clone ( RVal * dst, RVal * src );
int rval_descends ( RVal * needle, RVal * haystack );

#endif

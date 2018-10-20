#ifndef RILL_RVAL
#define RILL_RVAL

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct RStr RStr;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef enum RValType {
    RVT_NIL = 0,
    RVT_UXX = 1,
    RVT_IXX = 2,
    RVT_FXX = 3,
    RVT_STR = 4,
    RVT_VEC = 5,
    RVT_MAP = 10
} RValType;

typedef struct RVal {
    enum RValType type;
    union {
        unsigned long uxx;
        long          ixx;
        double        fxx;
        RStr *        str;
        RVec *        vec;
        RMap *        map;
        void *        udo;
    };
} RVal;

void rval_fzero ( RVal * val );
RValType rval_type ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
int rval_clone ( RVal * dst, RVal * src );
int rval_compact ( RVal * val );
int rval_lease ( RVal * val );
int rval_zero ( RVal * val );

#endif

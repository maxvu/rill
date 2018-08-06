#ifndef RILL_VAL_RVAL
#define RILL_VAL_RVAL

typedef struct RStr RStr;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef enum RValType {
    NIL,
    UXX,
    IXX,
    DBL,
    STR,
    VEC,
    MAP
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

int rval_init ( RVal * val, RValType type );
int rval_retire ( RVal * val );

RValType rval_type ( RVal * val );
int rval_contains ( RVal * haystack, RVal * needle );

int rval_copy ( RVal * dst, RVal * src );
int rval_clone ( RVal * dst, RVal * src );
void rval_lease ( RVal * val );
void rval_release ( RVal * val );
int rval_exclude ( RVal * val );

#endif

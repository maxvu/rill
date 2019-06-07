#ifndef RVM_RVAL
#define RVM_RVAL

#include <stddef.h>
#include <stdint.h>

typedef unsigned int rerr;

typedef enum rvtype {
    RVT_NIL = 0,
    RVT_IXX = 1,
    RVT_UXX = 2,
    RVT_FXX = 3,
    RVT_STR = 4,
    RVT_VEC = 5,
    RVT_MAP = 6
} rvtype;

typedef size_t rvinfo;

typedef struct rstr rstr;
typedef struct rvec rvec;
typedef struct rmap rmap;

typedef struct rval {
    rvinfo info;
    union {
        int          ixx;
        unsigned int uxx;
        double       fxx;
        rstr *       str;
        rvec *       vec;
        rmap *       map;
    };
} rval;

rvtype rval_type ( rval * val );
unsigned int rval_subtype ( rval * val );
rerr rval_settype ( rval * val, rvtype type );
rerr rval_setsubtype ( rval * val, unsigned int subtype );

rerr rval_lease ( rval * val );
rerr rval_release ( rval * val );
rerr rval_exclude ( rval * val );
int  rval_cyclesto ( rval * to, rval * from );

rerr rval_copy ( rval * dst, rval * src );
rerr rval_clone ( rval * dst, rval * src );
rerr rval_move ( rval * dst, rval * src );
rerr rval_swap ( rval * a, rval * b );

int rval_eq ( rval * a, rval * b );
int rval_truthy ( rval * val );

rval rnil ();

#endif

#ifndef RILL_RVAL_RVAL
#define RILL_RVAL_RVAL

#include "config.h"

typedef struct rbuf RBuf;
typedef struct rvec RVec;
typedef struct rmap RMap;

/*
    Lowest four bits reserved, rval type tag
    next eight bits reserved, user-type tag
*/

#define RILL_RVAL_TAG_TYPEMASK  0x000F
#define RILL_RVAL_TAG_UTYPEMASK 0x0FF0

typedef enum rvaltype {
    RVT_NIL = 0,
    RVT_IXX = 1,
    RVT_UXX = 2,
    RVT_FXX = 3,
    RVT_BUF = 4,
    RVT_VEC = 5,
    RVT_MAP = 6
} RValType;

typedef RILL_UXX_TYPE RValTag;
typedef RILL_UXX_TYPE RValUserTag;

uint8_t rvinfo_type ( RValTag tag );
void rvinfo_settype ( RValTag * tag, RValType type );

uint8_t rvt_getutype ( RValTag tag );
void rvt_setutype ( RValTag * tag );

typedef struct rval {
    RILL_UXX_TYPE info;
    union {
        RILL_IXX_TYPE ixx;
        RILL_UXX_TYPE uxx;
        RILL_FXX_TYPE fxx;
        RBuf *        buf;
        RVec *        vec;
        RMap *        map;
    };
} RVal;

RValTag rval_type ( RVal * val );
RValUserTag rval_usertype ( RVal * val );
int rval_usertype_set ( RVal * val, RValUserTag tag );
int rval_isnil ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
int rval_move ( RVal * dst, RVal * src );
int rval_clone ( RVal * dst, RVal * src );
int rval_swap ( RVal * a, RVal * b );
int rval_lease ( RVal * val );
int rval_release ( RVal * val );
int rval_subsume ( RVal * dst, RVal * src, RVal * container );
int rval_eq ( RVal * val );
int rval_dump ( RVal * val );

#endif

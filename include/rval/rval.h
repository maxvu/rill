#ifndef RILL_RVAL_RVAL
#define RILL_RVAL_RVAL

#include "config.h"
#include "rval/rval_type.h"
#include "rval/slab.h"

typedef struct RVal {
    RValType type;
    union {
        RILL_UXX_TYPE uxx;
        RILL_IXX_TYPE ixx;
        RILL_FXX_TYPE fxx;
        Slab        * slb;
    };
} RVal;

RVal rval_nil ();
RVal rval_uxx ( RILL_UXX_TYPE u );
RVal rval_ixx ( RILL_IXX_TYPE i );
RVal rval_fxx ( RILL_FXX_TYPE f );
RVal rval_buf ();
RVal rval_vec ();
RVal rval_map ();

int rval_type ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
int rval_swap ( RVal * a, RVal * b );
int rval_clone ( RVal * dst, RVal * src );
int rval_move ( RVal * dst, RVal * src );
void rval_lease ( RVal * val );
void rval_release ( RVal * val );
int rval_exclude ( RVal * val );
int rval_contains ( RVal * haystack, RVal * needle );
int rval_isfw ( RVal * val );
int rval_isnil ( RVal * val );
int rval_isfw ( RVal * val );
int rval_istruthy ( RVal * val );
int rval_eq ( RVal * val );
int rval_serialize ( RVal * dstbuf, RVal * val );

#endif

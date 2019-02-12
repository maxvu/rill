#ifndef RILL_RTYP_RTYP
#define RILL_RTYP_RTYP

typedef struct RVal RTyp;

typedef enum RTypKind {
    RTK_NAM, // type
    RTK_NIL, // built-in NIL
    RTK_IXX, // built-in IXX
    RTK_UXX, // built-in UXX
    RTK_FXX, // built-in FXX
    RTK_BUF, // built-in BUF
    RTK_VEC, // built-in VEC
    RTK_MAP, // built-in MAP
    RTK_TUP, // product type (tuple)
    RTK_UNN, // sum type (union)
    RTK_CMB, // combination type
    RTK_GEN, // generic
    RTK_WRD  // word
} RTypKind;

/*
    0: uxx rtypkind
    1: buf name
*/

typedef RVal RTyp;

RTypKind rtyp_kind ( RTyp * typ );
RVal * rtyp_name ( RTyp * typ );
int rtyp_isa ( RTyp * a, RTyp * b );

#endif

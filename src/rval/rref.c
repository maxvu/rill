#include "environment.h"

#include "rval/rbuf.h"
#include "rval/rvec.h"
#include "rval/rmap.h"

RRef rref_nil () {
    return (RRef){
        .type = RVT_NIL,
        .uxx  = 0
    };
}

RValType rref_type ( RRef * ref ) {
    TATTLE_IF( ref == NULL );
    return ref->type;
}

int rref_isfw ( RRef * val ) {
    TATTLE_IF( val == NULL );
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: return 1; break;
        case RVT_BUF:
        case RVT_VEC:
        case RVT_MAP: return 0; break;
    }
}

void rref_copy ( RRef * dst, RRef * src ) {

}

void rref_move ( RRef * dst, RRef * src ) {

}

void rref_swap ( RRef * a, RRef * b ) {

}

int rref_clone ( RRef * dst, RRef * src ) {

}

int rref_contains ( RRef * haystack, RRef * needle ) {

}

int rref_exclude ( RRef * dst, RRef * src ) {

}

void rref_ref ( RRef * val ) {
    TATTLE_IF( val == NULL );
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: return; break;
        case RVT_BUF: rbuf_ref( val->buf ); break;
        case RVT_VEC:
        case RVT_MAP: break;
    }
}

void rref_deref ( RRef * val ) {
    TATTLE_IF( val == NULL );
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: return 1; break;
        case RVT_BUF: rbuf_deref( val->buf ); break;
        case RVT_VEC:
        case RVT_MAP: return 0; break;
    }
}

int rref_eq ( RRef * a, RRef * b ) {
    TATTLE_IF( a == NULL );
    TATTLE_IF( b == NULL );
    if ( a->type != b->type )
        return 0;
    switch ( a->type ) {
        case RVT_NIL: return 1; break;
        case RVT_UXX: return a->uxx = b->uxx; break;
        case RVT_IXX: return a->ixx = b->ixx; break;
        case RVT_FXX: return a->fxx = b->fxx; break;
        case RVT_BUF: rbuf_cmp( a, b ) == 0; break;
        case RVT_VEC: rvec_eq( a, b ); break;
        case RVT_MAP: return 0; break;
    }
}

void rref_dump ( RRef * val ) {

}

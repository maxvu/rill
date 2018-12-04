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
    if ( ref == NULL ) {
        TATTLE;
        return 0;
    }
    return ref->type;
}

int rref_isfw ( RRef * val ) {
    if ( val == NULL ) {
        TATTLE;
        return 0;
    }
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: return 1; break;
        case RVT_BUF:
        case RVT_VEC:
        case RVT_MAP: return 0; break;
        default: return 0;
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
    if ( val == NULL ) {
        TATTLE;
        return;
    }
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
    if ( val == NULL ) {
        TATTLE;
        return;
    }
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: return; break;
        case RVT_BUF: rbuf_deref( val->buf ); break;
        case RVT_VEC: rvec_deref( val->vec ); break;
        // case RVT_MAP: rmap_deref( val->map ); break;
    }
}

int rref_eq ( RRef * a, RRef * b ) {
    if ( a == NULL ) {
        TATTLE;
        return 0;
    }
    if ( b == NULL ) {
        TATTLE;
        return 0;
    }
    if ( a->type != b->type )
        return 0;
    switch ( a->type ) {
        case RVT_NIL: return 1; break;
        case RVT_UXX: return a->uxx = b->uxx; break;
        case RVT_IXX: return a->ixx = b->ixx; break;
        case RVT_FXX: return a->fxx = b->fxx; break;
        case RVT_BUF: return rbuf_cmp( a->buf, b->buf ) == 0; break;
        case RVT_VEC: return rvec_eq( a->vec, b->vec ); break;
        case RVT_MAP: return 0; break;
    }
}

void rref_dump ( RRef * val ) {

}

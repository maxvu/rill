#include "environment.h"

#include "rval/rref.h"
#include "rval/rbuf.h"
#include "rval/rvec.h"
#include "rval/rmap.h"

RRef rref_nil () {
    return (RRef){
        .type = RVT_NIL,
        .uxx  = 0
    };
}

RRef rref_uxx ( RILL_UXX_TYPE u ) {
    return (RRef){
        .type = RVT_UXX,
        .uxx  = 0
    };
}

RRef rref_ixx ( RILL_IXX_TYPE i ) {
    return (RRef){
        .type = RVT_IXX,
        .ixx  = 0
    };
}

RRef rref_fxx ( RILL_FXX_TYPE f ) {
    return (RRef){
        .type = RVT_FXX,
        .fxx  = 0
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
    rref_release( dst );
    switch ( src->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: *dst = *src; break;
        case RVT_BUF:
            dst->type = RVT_BUF;
            dst->buf = src->buf;
            __rbuf_lease( src->buf );
        break;
        case RVT_VEC:
            dst->type = RVT_VEC;
            dst->vec = src->vec;
            __rvec_lease( src->vec );
        case RVT_MAP: break;
    }
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

void rref_lease ( RRef * val ) {
    if ( val == NULL ) {
        TATTLE;
        return;
    }
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: return; break;
        case RVT_BUF: __rbuf_lease( val->buf ); break;
        case RVT_VEC:
        case RVT_MAP: break;
    }
}

void rref_release ( RRef * val ) {
    if ( val == NULL ) {
        TATTLE;
        return;
    }
    switch ( val->type ) {
        case RVT_NIL:
        case RVT_UXX:
        case RVT_IXX:
        case RVT_FXX: return; break;
        case RVT_BUF: __rbuf_release( val->buf ); break;
        case RVT_VEC: __rvec_release( val->vec ); break;
        case RVT_MAP: /* rmap_release( val->map ); */ TATTLE; break;
    }
    val->type = RVT_NIL;
    val->uxx = 0;
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
        case RVT_UXX: return a->uxx == b->uxx; break;
        case RVT_IXX: return a->ixx == b->ixx; break;
        case RVT_FXX: return a->fxx == b->fxx; break;
        case RVT_BUF: return __rbuf_cmp( a->buf, b->buf ) == 0; break;
        case RVT_VEC: return __rvec_eq( a->vec, b->vec ); break;
        case RVT_MAP: return 0; break;
    }
}

void rref_dump ( RRef * val ) {

}

#include "rval/rnum.h"

RILL_UXX_TYPE __ruxx_get ( RRef * ref ) {
    if ( ref == NULL ) {
        TATTLE;
        return 0;
    }
    return ref->uxx;
}

void __ruxx_set ( RRef * ref, RILL_UXX_TYPE u ) {
    if ( ref == NULL ) {
        TATTLE;
        return;
    }
    if ( !rref_isfw( ref ) ) {
        TATTLE;
        return;
    }
    ref->uxx = u;
}

RILL_IXX_TYPE __rixx_get ( RRef * ref ) {
    if ( ref == NULL ) {
        TATTLE;
        return 0;
    }
    return ref->ixx;
}

void __rixx_set ( RRef * ref, RILL_IXX_TYPE i ) {
    if ( ref == NULL ) {
        TATTLE;
        return;
    }
    if ( !rref_isfw( ref ) ) {
        TATTLE;
        return;
    }
    ref->ixx = i;
}

RILL_FXX_TYPE __rfxx_get ( RRef * ref ) {
    if ( ref == NULL ) {
        TATTLE;
        return 0;
    }
    return ref->fxx;
}

void __rfxx_set ( RRef * ref, RILL_FXX_TYPE f ) {
    if ( ref == NULL ) {
        TATTLE;
        return;
    }
    if ( !rref_isfw( ref ) ) {
        TATTLE;
        return;
    }
    ref->fxx = f;
}

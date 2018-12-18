#include "rval/rnil.h"
#include "rval/rvec.h"

#include <string.h>
#include <stdlib.h>

int rvec_resize ( RVal * val, size_t new_cap ) {
    size_t target = sizeof( RVec ) + sizeof( RVal ) * new_cap;
    RVec * resized = RILL_REALLOC( val->vec, target );
    if ( !resized )
        return 0;
    val->vec = resized;
    val->vec->cap = new_cap;
    return 1;
}

RVal rvec ( size_t init_cap ) {
    RVal val = rnil();
    RVec * vec = RILL_ALLOC( sizeof( RVec ) + sizeof( RVal ) * init_cap );
    if ( !vec )
        return val;
    memset( vec, 0, sizeof( RVec ) + sizeof( RVal ) * init_cap );
    vec->ref = 1;
    vec->cap = init_cap;
    rvinfo_settype( &val.info, RVT_VEC );
    return val;
}

int rvec_reserve ( RVal * vecval, size_t new_cap ) {
    RILL_RVAL_ENFORCETYPE( vecval, RVT_VEC ) { return 0; }
    if ( vecval->vec->cap >= new_cap )
        return 1;
    return rvec_resize( vecval, new_cap );
}

int rvec_compact ( RVal * vecval ) {
    RILL_RVAL_ENFORCETYPE( vecval, RVT_VEC ) { return 0; }
    size_t target = vecval->vec->len;
    if ( target < RILL_RVEC_MINCAP )
        target = RILL_RVEC_MINCAP;
    return rvec_resize( vecval, target );
}

size_t rvec_len ( RVal * vecval ) {
    RILL_RVAL_ENFORCETYPE( vecval, RVT_VEC ) { return 0; }
    return vecval->vec->len;
}

RVal * rvec_get ( RVal * vecval, size_t index ) {
    RILL_RVAL_ENFORCETYPE( vecval, RVT_VEC ) { return 0; }
    if ( index >= vecval->vec->len )
        return NULL;
    return vecval->vec->vals + index;
}

int rvec_set ( RVal * vecval, size_t index, RVal * item ) {
    RILL_RVAL_ENFORCETYPE( vecval, RVT_VEC ) { return 0; }
    if ( !item ) { return 0; }
    if ( index >= vecval->vec->len )
        return 0;
    rval_copy( vecval->vec->vals + index, item );
    return 1;
}

int rvec_push ( RVal * vecval, RVal * item ) {
    RILL_RVAL_ENFORCETYPE( vecval, RVT_VEC ) { return 0; }
    if ( !item ) { return 0; }
    if ( !rvec_reserve( vecval, vecval->vec->cap * RILL_RVEC_GROWTHFACT ) )
        return 0;
    rval_copy( vecval->vec->vals + vecval->vec->len, item );
    vecval->vec->len += 1;
    return 1;
}

size_t rvec_pop ( RVal * vecval ) {
    RILL_RVAL_ENFORCETYPE( vecval, RVT_VEC ) { return 0; }
    if ( !vecval->vec->len )
        return 0;
    rval_release( vecval->vec->vals + vecval->vec->len - 1 );
    vecval->vec->len -= 1;
    return vecval->vec->len;
}

void rvec_clear ( RVal * vecval ) {
    RILL_RVAL_ENFORCETYPE( vecval, RVT_VEC ) { return; }
    for ( size_t i = 0; i < vecval->vec->len; i++ ) {
        rval_release( vecval->vec->vals + i );
    }
    vecval->vec->len = 0;
}

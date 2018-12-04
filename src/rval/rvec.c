#include "environment.h"

#include <string.h>

#include "rval/rvec.h"
#include "rval/rref.h"

int ____rvec_resize ( RVec * vec, size_t new_cap ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    if ( new_cap < vec->len ) {
        TATTLE;
        return 0;
    }
    RRef * new_vals = RILL_REALLOC( vec->vals, sizeof( RRef ) * new_cap );
    if ( new_vals == NULL )
        return 0;
    for ( size_t i = vec->len; i < new_cap; i++ )
        new_vals[ i ] = rref_nil();
    vec->vals = new_vals;
    vec->cap = new_cap;
    return 1;
}

RVec * __rvec_create ( size_t init_cap ) {
    if ( init_cap < RILL_RVEC_MINSIZE )
        init_cap = RILL_RVEC_MINSIZE;
    RVec * vec = RILL_ALLOC( sizeof( RVec ) );
    if ( vec == NULL )
        return 0;
    vec->vals = RILL_ALLOC( sizeof( RRef ) * init_cap );
    if ( vec->vals == NULL ) {
        free( vec );
        return 0;
    }
    for ( size_t i = 0; i < init_cap; i++ )
        vec->vals[ i ] = rref_nil();
    vec->len = 0;
    vec->cap = init_cap;
    vec->refcount = 1;
    return vec;
}

void __rvec_destroy ( RVec * vec ) {
    if ( vec == NULL ) {
        TATTLE;
        return;
    }
    __rvec_clear( vec );
    free( vec->vals );
    free( vec );
}

void __rvec_lease ( RVec * vec ) {
    if ( vec == NULL ) {
        TATTLE;
        return;
    }
    vec->refcount++;
}

void __rvec_release ( RVec * vec ) {
    if ( vec == NULL ) {
        TATTLE;
        return;
    }
    if ( !--vec->refcount )
        __rvec_destroy( vec );
}

int __rvec_unique ( RVec * vec ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    return vec->refcount == 1;
}

size_t __rvec_len ( RVec * vec ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    return vec->len;
}

int __rvec_reserve ( RVec * vec, size_t new_cap ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    if ( new_cap < RILL_RVEC_MINSIZE )
        new_cap = RILL_RVEC_MINSIZE;
    if ( vec->cap >= new_cap )
        return 1;
    return ____rvec_resize( vec, (double) new_cap * RILL_RVEC_GROWTHCOEFF );
}

int __rvec_compact ( RVec * vec ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    size_t target = vec->len;
    if ( target < RILL_RVEC_MINSIZE )
        target = RILL_RVEC_MINSIZE;
    if ( target == vec->cap )
        return 1;
    return ____rvec_resize( vec, target );
}

RRef * __rvec_get ( RVec * vec, size_t index ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    if ( vec->vals == NULL ) {
        TATTLE;
        return 0;
    }
    if ( index >= vec->len )
        return NULL;
    return vec->vals + index;
}

int __rvec_set ( RVec * vec, size_t index, RRef * ref ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    if ( vec->vals == NULL ) {
        TATTLE;
        return 0;
    }
    if ( index >= vec->len )
        return 0;
    rref_copy( vec->vals + index, ref );
    return 1;
}

int __rvec_push ( RVec * vec, RRef * ref ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    if ( vec->vals == NULL ) {
        TATTLE;
        return 0;
    }
    if ( !__rvec_reserve( vec, vec->len + 1 ) )
        return 0;
    vec->len++;
    if ( !__rvec_set( vec, vec->len - 1, ref ) ) {
        vec->len--;
        return 0;
    }
    return 1;
}

int __rvec_pop ( RVec * vec ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    if ( vec->vals == NULL ) {
        TATTLE;
        return 0;
    }
    if ( vec->len == 0 )
        return 0;
    rref_lease( vec->vals + vec->len - 1 );
    vec->len--;
    return 1;
}

int __rvec_concat ( RVec * vec, RVec * other ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    if ( other == NULL ) {
        TATTLE;
        return 0;
    }
    if ( !__rvec_reserve( vec, vec->len + other->len ) )
        return 0;
    vec->len += other->len;
    memcpy( vec->vals + vec->len, other->vals, sizeof( RRef ) * other->len );
    for ( size_t i = 0; i < other->len; i++ )
        rref_lease( other->vals + i );
    return 1;
}

int __rvec_fill ( RVec * vec, RRef * val, size_t n ) {
    if ( vec == NULL ) {
        TATTLE;
        return 0;
    }
    if ( val == NULL ) {
        TATTLE;
        return 0;
    }
    if ( !__rvec_reserve( vec, vec->len + n ) )
        return 0;
    vec->len += n;
    for ( size_t i = 0; i < n; i++ )
        __rvec_push( vec, val );
    return 1;
}

void __rvec_clear ( RVec * vec ) {
    if ( vec == NULL ) {
        TATTLE;
        return;
    }
    for ( size_t i = 0; i < vec->len; i++ )
        rref_release( vec->vals + i );
    memset( vec->vals, 0, sizeof( RRef ) * vec->len );
    vec->len = 0;
}

int __rvec_eq ( RVec * a, RVec * b ) {
    if ( a == NULL ) {
        TATTLE;
        return 0;
    }
    if ( b == NULL ) {
        TATTLE;
        return 0;
    }
    if ( a->len != b->len ) return 0;
    for ( size_t i = 0; i < a->len; i++ )
        if ( !rref_eq( a->vals + i, b->vals + i ) )
            return 0;
    return 1;
}

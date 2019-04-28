#include "config/rerr.h"
// #include "rlex/rlex.h"
#include "rlex/rlextok.h"
#include "rval/rval.h"
#include "rval/rbuf.h"
#include "rval/rvec.h"
#include "rval/ruxx.h"

#include <stdio.h>

int rlextok (
    RVal * tok,
    unsigned int type,
    RILL_UXX_TYPE line,
    RILL_UXX_TYPE pos,
    RVal * text
) {
    RVal tmp = rnil();
    if ( !rvec_init( tok, 4 ) )
        return 0;

    ruxx_set( &tmp, type );
    rvec_push( tok, &tmp );

    ruxx_set( &tmp, line );
    rvec_push( tok, &tmp );

    ruxx_set( &tmp, pos );
    rvec_push( tok, &tmp );

    rvec_push( tok, text );

    return 1;
}

int rlextok_type ( RVal * token ) {
    RILL_ASSERT_ARGNOTNULL( token )
    if ( rvec_len( token ) != 4 )
        return -1;
    return ruxx_get( rvec_get( token, 0 ) );
}

RVal * rlextok_line ( RVal * token ) {
    RILL_ASSERT_ARGNOTNULL( token )
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 1 );
}

RVal * rlextok_pos  ( RVal * token ) {
    RILL_ASSERT_ARGNOTNULL( token )
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 2 );
}

RVal * rlextok_text  ( RVal * token ) {
    RILL_ASSERT_ARGNOTNULL( token )
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 3 );
}

int rlextok_dump ( RVal * token ) {
}

#include "rlex/rlextok.h"
#include "rval/rval.h"
#include "rval/rvec.h"
#include "rval/ruxx.h"

int rlextok (
    RVal * tok,
    unsigned int type,
    RILL_UXX_TYPE line,
    RILL_UXX_TYPE pos,
    RVal * text
) {
    RVal tmp = rnil();
    if ( !rvec_init( tok, 4 ) ) {
        rval_release( tok );
        rval_release( &tmp );
        return 0;
    }

    ruxx_set( &tmp, type );
    rvec_push( tok, &tmp );

    ruxx_set( &tmp, line );
    rvec_push( tok, &tmp );

    ruxx_set( &tmp, pos );
    rvec_push( tok, &tmp );

    return 1;
}

RVal * rlextok_type ( RVal * token ) {
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 0 );
}

RVal * rlextok_line ( RVal * token ) {
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 1 );
}

RVal * rlextok_pos  ( RVal * token ) {
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 2 );
}

RVal * rlextok_text  ( RVal * token ) {
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 3 );
}

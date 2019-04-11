#include "rlex/rlextok.h"
#include "rlex/types.h"
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

RVal * rlextok_dump  ( RVal * token ) {
    switch ( ruxx_get( rvec_get( token, 0 ) ) ) {
        case RLXTOK_WHITESPACE:
            printf( "WHITESPACE" );
            break;
        case RLXTOK_COMMENT:
            printf( "COMMENT" );
            break;
        case RLXTOK_IDENTIFIER:
            printf( "IDENTIFIER" );
            break;
        case RLXTOK_NUMBER:
            printf( "NUMBER" );
            break;
        case RLXTOK_STRING_OPEN:
            printf( "STRING_OPEN" );
            break;
        case RLXTOK_STRING_CLOSE:
            printf( "STRING_CLOSE" );
            break;
        case RLXTOK_LIST_OPEN:
            printf( "LIST_OPEN" );
            break;
        case RLXTOK_LIST_CLOSE:
            printf( "LIST_CLOSE" );
            break;
        case RLXTOK_HASH_OPEN:
            printf( "HASH_OPEN" );
            break;
        case RLXTOK_HASH_CLOSE:
            printf( "HASH_CLOSE" );
            break;
        case RLXTOK_QUOTE_OPEN:
            printf( "QUOTE_OPEN" );
            break;
        case RLXTOK_QUOTE_CLOSE:
            printf( "QUOTE_CLOSE" );
            break;
        case RLXTOK_WORD_OPEN:
            printf( "WORD_OPEN" );
            break;
        case RLXTOK_WORD_CLOSE:
            printf( "WORD_CLOSE" );
            break;
    }
    printf(
        " @ %lu:%lu '%s'\n",
        ruxx_get( rvec_get( token, 1 ) ),
        ruxx_get( rvec_get( token, 2 ) ),
        rbuf_get( rvec_get( token, 3 ) )
    );
}

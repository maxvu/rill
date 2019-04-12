#include "config/rerr.h"
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

int rlextok_type ( RVal * token ) {
    if ( rvec_len( token ) != 4 )
        return -1;
    return ruxx_get( rvec_get( token, 0 ) );
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

int rlextok_dump ( RVal * token ) {
    RILL_ASSERT_ARGNOTNULL( token );
    RVal type = rnil();
    if ( !rbuf_init( &type, 32 ) )
        return 0;
    switch ( rlextok_type( token ) ) {
        case RILL_LEXTOK_WHITESPACE:
            if ( !rbuf_strcpy( &type, "whitespace" ) )
                goto err;
            break;
        case RILL_LEXTOK_IDENTIFIER:
            if ( !rbuf_strcpy( &type, "identifier" ) )
                goto err;
            break;
        case RILL_LEXTOK_NUMBER:
            if ( !rbuf_strcpy( &type, " number" ) )
                goto err;
            break;
        case RILL_LEXTOK_COMMENT_OPEN:
            if ( !rbuf_strcpy( &type, "comment-open" ) )
                goto err;
            break;
        case RILL_LEXTOK_COMMENT_CLOSE:
            if ( !rbuf_strcpy( &type, "comment-close" ) )
                goto err;
            break;
        case RILL_LEXTOK_STRING_OPEN:
            if ( !rbuf_strcpy( &type, "string-open" ) )
                goto err;
            break;
        case RILL_LEXTOK_STRING_CLOSE:
            if ( !rbuf_strcpy( &type, "string-close" ) )
                goto err;
            break;
        case RILL_LEXTOK_ENUM_OPEN:
            if ( !rbuf_strcpy( &type, "enum-open" ) )
                goto err;
            break;
        case RILL_LEXTOK_ENUM_CLOSE:
            if ( !rbuf_strcpy( &type, "enum-close" ) )
                goto err;
            break;
        case RILL_LEXTOK_QUOTE_OPEN:
            if ( !rbuf_strcpy( &type, "quotation-open" ) )
                goto err;
            break;
        case RILL_LEXTOK_QUOTE_CLOSE:
            if ( !rbuf_strcpy( &type, "quotation-close" ) )
                goto err;
            break;
        case RILL_LEXTOK_COMPILE_OPEN:
            if ( !rbuf_strcpy( &type, "compile-open" ) )
                goto err;
            break;
        case RILL_LEXTOK_COMPILE_CLOSE:
            if ( !rbuf_strcpy( &type, "compile-close" ) )
                goto err;
            break;
        default:
            if ( !rbuf_strcpy( &type, "?? unknown ??" ) )
                goto err;
    }
    printf(
        "(%s) @ line %lu, pos %lu: `%s`\n",
        rbuf_get( &type ),
        ruxx_get( rlextok_line( token ) ),
        ruxx_get( rlextok_pos( token ) ),
        rbuf_get( rlextok_text( token ) )
    );
    rval_release( &type );
    return 1;

    err:
        rval_release( &type );
        return 0;
}

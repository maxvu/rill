#include "config/rerr.h"
#include "rlex/rlextok.h"
#include "rlex/types.h"
#include "rval/rval.h"
#include "rval/rbuf.h"
#include "rval/rvec.h"
#include "rval/ruxx.h"

#include <stdio.h>

int rlextok (
    rval * tok,
    unsigned int type,
    RILL_UXX_TYPE line,
    RILL_UXX_TYPE pos,
    rval * text
) {
    rval tmp = rnil();
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

int rlextok_type ( rval * token ) {
    if ( rvec_len( token ) != 4 )
        return -1;
    return ruxx_get( rvec_get( token, 0 ) );
}

rval * rlextok_line ( rval * token ) {
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 1 );
}

rval * rlextok_pos  ( rval * token ) {
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 2 );
}

rval * rlextok_text  ( rval * token ) {
    if ( rvec_len( token ) != 4 )
        return NULL;
    return rvec_get( token, 3 );
}

int rlextok_dump ( rval * token ) {
    RILL_ASSERT_ARGNOTNULL( token );
    rval type = rnil();
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
        case RILL_LEXTOK_STRING:
            if ( !rbuf_strcpy( &type, "string" ) )
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

#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rlex/rlexchr.h"
#include "rlex/rlexstt.h"
#include "rlex/rlextok.h"
#include "rval/rbuf.h"
#include "rval/ruxx.h"
#include "rval/rvec.h"

#include <stdio.h>

int rlex_whitespace ( rlexstt * stt );
int rlex_comment ( rlexstt * stt );
int rlex_identifier ( rlexstt * stt );
int rlex_number ( rlexstt * stt );
int rlex_string ( rlexstt * stt );

int rlex ( rlexstt * stt, uint8_t * begin, uint8_t * end ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    RILL_ASSERT_ARGNOTNULL( begin );
    RILL_ASSERT_ARGNOTNULL( end );

    int c;

    if ( !rlexstt_init( stt, begin, end ) )
        return 0;

    while ( !rlexstt_done( stt ) ) {
        c = rlexstt_cdpt( stt );

        if ( rlexchr_ws( c ) ) {
            rlex_whitespace( stt );
            continue;
        }

        if ( rlexchr_idopen( c ) ) {
            rlex_identifier( stt );
            continue;
        }

        if ( rlexchr_numopen( c ) ) {
            rlex_number( stt );
            continue;
        }

        switch ( c ) {
            case RILL_LEX_CHAR_STRING_DELIM_SINGLE:
            case RILL_LEX_CHAR_STRING_DELIM_DOUBLE:
                rlex_string( stt );
                continue;
            case RILL_LEX_CHAR_COMMENT_BEGIN:
                rlex_comment( stt );
                continue;
            case RILL_LEX_CHAR_STRUCT_BEGIN:
                rlexstt_step( stt );
                rlexstt_range( stt, RILL_LEXTOK_STRUCT_OPEN );
                continue;
            case RILL_LEX_CHAR_STRUCT_END:
                rlexstt_step( stt );
                rlexstt_range( stt, RILL_LEXTOK_STRUCT_CLOSE );
                continue;
            case RILL_LEX_CHAR_QUOTE_BEGIN:
                rlexstt_step( stt );
                rlexstt_range( stt, RILL_LEXTOK_QUOTE_OPEN );
                continue;
            case RILL_LEX_CHAR_QUOTE_END:
                rlexstt_step( stt );
                rlexstt_range( stt, RILL_LEXTOK_QUOTE_CLOSE );
                continue;
            case RILL_LEX_CHAR_COMPILE_MODE_BEGIN:
                rlexstt_step( stt );
                rlexstt_range( stt, RILL_LEXTOK_COMPILE_OPEN );
                continue;
            case RILL_LEX_CHAR_COMPILE_MODE_END:
                rlexstt_step( stt );
                rlexstt_range( stt, RILL_LEXTOK_COMPILE_CLOSE );
                continue;
            default:
                stt->status = RILL_LEX_UNEXPECTED_CHAR;
                break;
        }
    }

    done:
    return rlexstt_ok( stt );
}

int rlex_comment ( rlexstt * stt ) {
    if ( !rlexstt_step( stt ) ) {
        stt->status = RILL_LEX_UNCLOSED_COMMENT;
        return 0;
    }
    while ( !rlexstt_done( stt ) ) {
        rlexstt_step( stt );
        if ( rlexstt_cdpt( stt ) == RILL_LEX_CHAR_COMMENT_END ) {
            rlexstt_step( stt );
            return rlexstt_range( stt, RILL_LEXTOK_COMMENT );
        }
    }

    if ( rlexstt_ok( stt ) )
        stt->status = RILL_LEX_UNCLOSED_COMMENT;
    return 0;
}

int rlex_whitespace ( rlexstt * stt ) {
    while ( !rlexstt_done( stt ) && rlexchr_ws( rlexstt_cdpt( stt ) ) )
        rlexstt_step( stt );
    return rlexstt_range( stt, RILL_LEXTOK_WHITESPACE );
}

int rlex_identifier ( rlexstt * stt ) {
    while ( !rlexstt_done( stt ) && rlexchr_idbody( rlexstt_cdpt( stt ) ) )
        rlexstt_step( stt );
    if ( rlexstt_ok( stt ) )
        return rlexstt_range( stt, RILL_LEXTOK_IDENTIFIER );
    return 0;
}

int rlex_number ( rlexstt * stt ) {
    while ( !rlexstt_done( stt ) && rlexchr_numbody( rlexstt_cdpt( stt ) ) )
        rlexstt_step( stt );
    if ( rlexstt_ok( stt ) )
        return rlexstt_range( stt, RILL_LEXTOK_NUMBER );
    return 0;
}

int rlex_string ( rlexstt * stt ) {
    int delim = rlexstt_cdpt( stt );
    int prev = 0;
    int esc = RILL_LEX_CHAR_STRING_ESCAPE;
    while ( !rlexstt_done( stt ) ) {
        rlexstt_step( stt );
        if ( rlexstt_cdpt( stt ) == delim && prev != esc ) {
            rlexstt_step( stt );
            return rlexstt_range( stt, RILL_LEXTOK_STRING );
        }
        prev = rlexstt_cdpt( stt );
    }
    if ( rlexstt_ok( stt ) )
        stt->status = RILL_LEX_UNCLOSED_STRING;
    return 0;
}

void rlex_dump ( rval * result ) {
    size_t n = rvec_len( result );
    rval * token, *type, * text, * line, * offset;
    for ( size_t i = 0; i < n; i++ ) {
        token = rvec_get( result, i );
        type = rvec_get( token, 0 );
        text = rvec_get( token, 1 );
        line = rvec_get( token, 2 );
        offset = rvec_get( token, 3 );
        switch ( ruxx_get( type ) ) {
            case RILL_LEXTOK_WHITESPACE:
                printf(
                    "WHITESPACE<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_IDENTIFIER:
                printf(
                    "IDENTIFIER<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_NUMBER:
                printf(
                    "NUMBER<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_STRING:
                printf(
                    "STRING<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_COMMENT:
                printf(
                    "COMMENT<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_STRUCT_OPEN:
                printf(
                    "STRUCT_OPEN<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_STRUCT_CLOSE:
                printf(
                    "STRUCT_CLOSE<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_QUOTE_OPEN:
                printf(
                    "QUOTE_OPEN<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_QUOTE_CLOSE:
                printf(
                    "QUOTE_CLOSE<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_COMPILE_OPEN:
                printf(
                    "COMPILE_OPEN<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
            case RILL_LEXTOK_COMPILE_CLOSE:
                printf(
                    "COMPILE_CLOSE<%s> @ line %lu, offset %lu, length %lu\n",
                    rbuf_get( text ),
                    ruxx_get( line ),
                    ruxx_get( offset ),
                    rbuf_len( text )
                );
                break;
        }
    }
}

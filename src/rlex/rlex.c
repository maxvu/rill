#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rlex/rlexchr.h"
#include "rlex/rlexit.h"
#include "rlex/rlextok.h"
#include "rval/rbuf.h"
#include "rval/rval.h"
#include "rval/rvec.h"

int rlex_ws ( rval * out, rlexit * begin, int * status );
int rlex_id ( rval * out, rlexit * begin, int * status );
int rlex_str ( rval * out, rlexit * begin, int * status );
int rlex_num ( rval * out, rlexit * begin, int * status );
int rlex_cmt ( rval * out, rlexit * begin, int * status );

int rlex_tokensingle ( rval * out, rlexit * it, uint8_t c, int type );
int rlex_tokenrange (
    rval * out,
    rlexit * begin,
    rlexit * end,
    int type
);

int rlex ( rval * result, rlexit * it, rval * input, int * status ) {
    RILL_ASSERT_ARGNOTNULL( result )
    RILL_ASSERT_ISBUF( input )
    RILL_ASSERT_ARGNOTNULL( status )

    int c;
    rval out = rvecq();

    if ( rval_isnil( &out ) )
        return 0;
    {
        uint8_t * begin = rbuf_get( input );
        uint8_t * end = begin + rbuf_len( input );
        if ( !rlexit_init( &it, begin, end ) )
            goto err;
    }

    while ( !rlexit_done( &it ) ) {
        c = rlexit_cdpt( &it );
        if ( rlexchr_ws( c ) && !rlex_ws( &out, &it, status ) )
            goto err;
        if ( rlexchr_idopen( c ) && !rlex_id( &out, &it, status ) )
            goto err;
        if ( rlexchr_numopen( c ) && !rlex_num( &out, &it, status ) )
            goto err;
        switch ( c ) {
            case RILL_LEX_CHAR_STRING_DELIM_SINGLE:
            case RILL_LEX_CHAR_STRING_DELIM_DOUBLE:
                if ( !rlex_str( &out, &it, status ) )
                    goto err; else continue;
                break;
            case RILL_LEX_CHAR_STRUCT_BEGIN:
                if ( !rlex_tokensingle(
                    &out,
                    &it,
                    RILL_LEX_CHAR_STRUCT_BEGIN,
                    RILL_LEXTOK_STRUCT_OPEN
                ) )
                    goto err; else continue;
                break;
            case RILL_LEX_CHAR_STRUCT_END:
                if ( !rlex_tokensingle(
                    &out,
                    &it,
                    RILL_LEX_CHAR_STRUCT_END,
                    RILL_LEXTOK_STRUCT_CLOSE
                ) )
                    goto err; else continue;
                break;
            case RILL_LEX_CHAR_QUOTE_BEGIN:
                if ( !rlex_tokensingle(
                    &out,
                    &it,
                    RILL_LEX_CHAR_QUOTE_BEGIN,
                    RILL_LEXTOK_QUOTE_OPEN
                ) )
                    goto err; else continue;
                break;
            case RILL_LEX_CHAR_QUOTE_END:
                if ( !rlex_tokensingle(
                    &out,
                    &it,
                    RILL_LEX_CHAR_QUOTE_END,
                    RILL_LEXTOK_QUOTE_CLOSE
                ) )
                    goto err; else continue;
                break;
            case RILL_LEX_CHAR_COMMENT_BEGIN:
                if ( !rlex_cmt( &out, &it, status ) )
                    goto err; else continue;
                break;
            case RILL_LEX_CHAR_COMPILE_MODE_BEGIN:
                if ( !rlex_tokensingle(
                    &out,
                    &it,
                    RILL_LEX_CHAR_COMPILE_MODE_BEGIN,
                    RILL_LEXTOK_COMPILE_OPEN
                ) )
                    goto err; else continue;
                break;
            case RILL_LEX_CHAR_COMPILE_MODE_END:
                if ( !rlex_tokensingle(
                    &out,
                    &it,
                    RILL_LEX_CHAR_COMPILE_MODE_END,
                    RILL_LEXTOK_COMPILE_CLOSE
                ) )
                    goto err; else continue;
                break;
        }
    }

    if ( !rval_copy( result, &out ) )
        goto err;
    rval_release( &result );
    return 1;

    err:

        rlexit_retire( &it );
        rval_release( &out );
            return 0;
}

int rlex_tokensingle ( rval * out, rlexit * it, uint8_t c, int type ) {
    int ok = 1;
    rval text = rnil();
    rval token = rnil();

    if ( !rbuf_init( &text, 2 ) )
        goto err;
    if ( !rbuf_memcpy( &token, &text, 1 ) )
        goto err;
    {
        size_t line = rlexit_lineno( it );
        size_t pos = rlexit_linepos( it );
        if ( !rlextok( &token, type, line, pos, &text ) )
            goto err;
    }
    if ( !rvec_push( out, &token ) )
        goto err;

    err:
        ok = 0;
    done:
        rval_release( &text );
        rval_release( &token );
        return ok;
}

int rlex_tokenrange (
    rval * out,
    rlexit * begin,
    rlexit * end,
    int type
) {
    rval text = rbufq();
    rval token = rnil();
    char ok = 1;

    if ( rval_isnil( &text ) )
        goto err;
    {
        uint8_t * text_begin = rlexit_text( begin );
        uint8_t * text_end = rlexit_text( end );
        if ( !rbuf_memcpy( &text, rlexit_text( it ), end - begin ) )
            goto err;
    }
    size_t line = rlexit_lineno( begin );
    size_t pos = rlexit_linepos( begin );
    if ( !rlextok( &token, type, line, pos, &text ) )
        goto err;
    if ( !rvec_push( out, &token ) )
        goto err;
    goto done;

    err:
        ok = 0;
    done:
        rval_release( &text );
        rval_release( &token );
        return ok;
}

int rlex_ws ( rval * out, rlexit * begin, int * status ) {
    rlexit it;
    char ok = 1;
    if ( !rlexit_copy( &it, begin ) )
        return 0;
    while ( !rlexit_done( &it ) && rlexchr_ws( rlexit_cdpt( &it ) ) ) {
        rlexit_step( &it );
    }
    rval token = rnil();
    if ( !rlexit_range( &token, begin, &it, RILL_LEXTOK_WHITESPACE ) ) {
        ok = 0;
        goto done;
    }
    if ( rvec_push( out, &token ) ) {
        ok = 0;
        goto done;
    }

    done:
        rval_release( &token );
        rlexit_retire( &it );
        return ok;
}

int rlex_ws ( rval * out, rlexit * begin, int * status ) {
    rlexit it;
    int ok = 1;
    if ( !rlexit_copy( &it, begin ) )
        return 0;
    while ( !rlexit_done( &end ) && rlexchr_ws( rlexit_cdpt( &end ) ) )
        rlexit_step( &end );
    if ( !rlexit_ok( &end ) )
        goto err;
    if ( !rlex_tokenrange( out, begin, &it, RILL_LEXTOK_WHITESPACE )
        goto err;
    goto done;

    err:
        ok = 0;
    done:
        rlexit_retire( &it );
        return ok
}

int rlex_id ( rval * out, rlexit * begin, int * status ) {
    rlexit it;
    int ok = 1;
    if ( !rlexit_copy( &it, begin ) )
        return 0;
    while ( !rlexit_done( &end ) && rlexchr_idbody( rlexit_cdpt( &end ) ) )
        rlexit_step( &end );
    if ( !rlexit_ok( &end ) )
        goto err;
    if ( !rlex_tokenrange( out, begin, &it, RILL_LEXTOK_IDENTIFIER )
        goto err;
    goto done;

    err:
        ok = 0;
    done:
        rlexit_retire( &it );
        return ok
}

int rlex_str ( rval * out, rlexit * begin, int * status );
int rlex_num ( rval * out, rlexit * begin, int * status );
int rlex_cmt ( rval * out, rlexit * begin, int * status );

#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rlex/rlexchr.h"
#include "rlex/rlexit.h"
#include "rval/rbuf.h"
#include "rval/rval.h"

int rlex_ws ( rlexit * it );
int rlex_id ( rlexit * it );
int rlex_str ( rlexit * it );
int rlex_num ( rlexit * it );
int rlex_cmt ( rlexit * it );

int rlex_stresc ( rlexit * it );
int rlex_stresc_char ( rlexit * it );
int rlex_stresc_cdpt ( rlexit * it );

int rlex ( rval * dst, rval * lexbuf ) {
    RILL_ASSERT_ARGNOTNULL( dst )
    RILL_ASSERT_ISBUF( lexbuf )

    rlexit it;
    rval result;
    int c;

    if ( !rlexit_init( &it, lexbuf ) ) {
        it.err = RILL_LEXIT_UNDERLYING_ERROR;
        return 0;
    }

    result = rnil();
    if ( !rbuf_init( &result, RILL_LEXIT_DEFAULT_BUFFER_SIZE ) )
        goto err;

    step:

        if ( rlexit_step( &it ) ) {
            if ( !rlexit_ok( &it ) )
                goto err;
            goto done;
        }

        c = rlexit_peek( &it );

        if ( rlexchr_ws( c ) ) {
            if ( !rlex_ws( &it ) )
                goto err;
            goto step;
        }
        if ( rlexchr_numopen( c ) ) {
            if ( !rlex_num( &it ) )
                goto err;
            goto step;
        }

        switch ( c ) {
            case RILL_LEX_CHAR_STRING_DELIM_SINGLE:
            case RILL_LEX_CHAR_STRING_DELIM_DOUBLE:
                if ( !rlex_str( &it ) )
                    goto err;
                goto step;
            case RILL_LEX_CHAR_HASH_BEGIN:
                if ( !rlexit_clipchar( &it, RILL_LEXTOK_HASH_OPEN ) )
                    goto err;
                goto step;
            case RILL_LEX_CHAR_HASH_END:
                if ( !rlexit_clipchar( &it, RILL_LEXTOK_HASH_CLOSE ) )
                    goto err;
                goto step;
            case RILL_LEX_CHAR_LIST_BEGIN:
                if ( !rlexit_clipchar( &it, RILL_LEXTOK_LIST_OPEN ) )
                    goto err;
                goto step;
            case RILL_LEX_CHAR_LIST_END:
                if ( !rlexit_clipchar( &it, RILL_LEXTOK_LIST_CLOSE ) )
                    goto err;
                goto step;
            case RILL_LEX_CHAR_QUOTE_BEGIN:
                if ( !rlexit_clipchar( &it, RILL_LEXTOK_QUOTE_OPEN ) )
                    goto err;
                goto step;
            case RILL_LEX_CHAR_QUOTE_END:
                if ( !rlexit_clipchar( &it, RILL_LEXTOK_QUOTE_CLOSE ) )
                    goto err;
                goto step;
            case RILL_LEX_CHAR_COMPILE_MODE_BEGIN:
                if ( !rlexit_clipchar( &it, RILL_LEXTOK_COMPILE_OPEN ) )
                    goto err;
                goto step;
            case RILL_LEX_CHAR_COMPILE_MODE_END:
                if ( !rlexit_clipchar( &it, RILL_LEXTOK_COMPILE_CLOSE ) )
                    goto err;
                goto step;
            case RILL_LEX_CHAR_COMMENT_BEGIN:
                if ( !rlex_cmt( &it ) )
                    goto err;
                goto step;
            default:
            break;
        }

        rlexit_seterr( &it, RILL_LEXIT_UNEXPECTED_CHAR );
        goto err;

    done:

        rval_copy( dst, &result );
        rval_release( &result );
        rlexit_retire( &it );
        return 1;

    err:
        rval_release( &result );
        rlexit_retire( &it );
        return 0;
}

int rlex_ws ( rlexit * it ) {

}

int rlex_id ( rlexit * it ) {

}

int rlex_str ( rlexit * it ) {

}

int rlex_cmt ( rlexit * it ) {

}

int rlex_stresc ( rlexit * it ) {

}

int rlex_stresc_char ( rlexit * it ) {

}

int rlex_stresc_cdpt ( rlexit * it ) {

}

int rlex_dump ( rval * lexbuf ) {

}

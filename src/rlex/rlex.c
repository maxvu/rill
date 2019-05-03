#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rlex/rlexchr.h"
#include "rlex/rlextok.h"
#include "rval/rbuf.h"
#include "rval/rval.h"
#include "rval/rvec.h"

typedef struct rlexstate {
    rutf8it uit;
    rval * result;
    size_t line;
    size_t offset;
    int * status;
} rlexstate;

int rlexstate_step ( rlexstate * state ) {
    if ( rutf8it_done( &state->uit ) )
        return 0;
    if ( rutf8it_cdpt( &state->uit ) == RILL_LEX_CHAR_LINE_FEED ) {
        state->line++;
        state->offset = 0;
    } else {
        state->offset++;
    }
    return rutf8it_step( &state->uit );
}

int rlexstate_range ( rlexstate * begin, rlexstate * end, int type ) {
    char ok = 1;
    rval text = rbufq();
    rval token = rnil();

    if ( rval_isnil( &text ) )
        return 0;
    {
        uint8_t * a = rutf8it_pos( &begin->uit );
        uint8_t * b = rutf8it_pos( &end->uit );
        if ( rbuf_memcpy( &text, a, b - a ) )
            goto err;
    }

    if ( !rlextok( &token, type, begin->line, begin->offset, &text ) )
        goto err;
    if ( !rvec_push( begin->result, &token ) )
        goto err;
    goto done;

    err:
        ok = 0;
    done:
        rval_release( &text );
        rval_release( &token );
        return ok;
}

int rlex_ws ( rlexstate * state );
int rlex_id ( rlexstate * state );
int rlex_num ( rlexstate * state );
int rlex_str ( rlexstate * state );
int rlex_cmt ( rlexstate * state );
int rlex_single ( rlexstate * state, int type );
int rlex_token ( rlexstate * state, int (*test)(int), int type );

int rlex ( rval * result, rutf8it * it, int * status ) {
    RILL_ASSERT_ARGNOTNULL( result )
    RILL_ASSERT_ARGNOTNULL( it )
    RILL_ASSERT_ARGNOTNULL( status )

    if ( rval_type( result ) != RVT_VEC ) {
        *result = rvecq();
        if ( rval_isnil( result ) ) {
            *status = RILL_LEX_UNDERLYING_ERROR;
            return 0;
        }
    }

    int c;
    char ok = 1;
    rlexstate state = {
        .uit = *it,
        .result = result,
        .line = 1,
        .offset = 0,
        .status = status
    };

    while ( !rutf8it_done( it ) ) {
        c = rutf8it_cdpt( it );

        if ( rlexchr_ws( c ) )
            if ( !rlex_token( &state, rlexchr_ws, RILL_LEXTOK_WHITESPACE ) )
                return 0;

        if ( rlexchr_idopen( c ) )
            if ( !rlex_token( &state, rlexchr_idbody, RILL_LEXTOK_IDENTIFIER ) )
                return 0;

        if ( rlexchr_idopen( c ) )
            if ( !rlex_token( &state, rlexchr_numbody, RILL_LEXTOK_NUMBER ) )
                return 0;

        switch ( c ) {
            case RILL_LEX_CHAR_STRING_DELIM_SINGLE:
            case RILL_LEX_CHAR_STRING_DELIM_DOUBLE:
                if ( !rlex_str( &state ) )
                    goto err;
                break;
            case RILL_LEX_CHAR_COMMENT_BEGIN:
                if ( !rlex_cmt( &state ) )
                    goto err;
                break;
            case RILL_LEX_CHAR_STRUCT_BEGIN:
                if ( !rlex_single( &state, RILL_LEXTOK_STRUCT_OPEN ) )
                    goto err;
                break;
            case RILL_LEX_CHAR_STRUCT_END:
                if ( !rlex_single( &state, RILL_LEXTOK_STRUCT_CLOSE ) )
                    goto err;
                break;
            case RILL_LEX_CHAR_QUOTE_BEGIN:
                if ( !rlex_single( &state, RILL_LEXTOK_QUOTE_OPEN ) )
                    goto err;
                break;
            case RILL_LEX_CHAR_QUOTE_END:
                if ( !rlex_single( &state, RILL_LEXTOK_QUOTE_CLOSE ) )
                    goto err;
                break;
            case RILL_LEX_CHAR_COMPILE_MODE_BEGIN:
                if ( !rlex_single( &state, RILL_LEXTOK_COMPILE_OPEN ) )
                    goto err;
                break;
            case RILL_LEX_CHAR_COMPILE_MODE_END:
                if ( !rlex_single( &state, RILL_LEXTOK_COMPILE_CLOSE ) )
                    goto err;
                break;
        }
    }
    goto done;

    err:
        ok = 0;
    done:
        *it = state.uit;
        return ok;
}

int rlex_single ( rlexstate * state, int type ) {
    int ok = 1;
    rval text = rnil();
    rval token = rnil();

    if ( !rbuf_init( &text, 1 ) )
        goto err;
    if ( !rbuf_memcpy( &text, rutf8it_pos( &state->uit ), 1 ) )
        goto err;
    if ( !rlextok( &token, type, state->line, state->offset, &text ) )
        goto err;
    if ( !rvec_push( state->result, &token ) )
        goto err;

    goto done;

    err:
        ok = 0;
    done:
        rval_release( &text );
        rval_release( &token );
        return ok;
}

int rlex_token ( rlexstate * state, int (*test)(int), int type ) {
    rlexstate begin = *state;
    while ( !rutf8it_done( &state->uit ) &&
        test( rutf8it_cdpt( &state->uit ) )
    ) {
        rlexstate_step( state );
    }
    if ( !rutf8it_ok( &state->uit ) ) {
        *state->status = RILL_LEX_INVALID_UTF8;
        return 0;
    }
    if ( !rlexstate_range( &begin, state, type ) ) {
        *state->status = RILL_LEX_UNDERLYING_ERROR;
        return 0;
    }
    return 1;
}

int rlex_str ( rlexstate * state ) {
    int prev = 0;
    int curr = 0;
    int delim = rutf8it_cdpt( &state->uit );

    rlexstate begin = *state;

    while ( !rutf8it_done( &state->uit ) ) {
        if ( !rlexstate_step( state ) )
            break;
        curr = rutf8it_cdpt( &state->uit );
        if ( curr == delim && prev != RILL_LEX_CHAR_STRING_ESCAPE )
            break;
        prev = curr;
    }

    if ( rutf8it_done( &state->uit ) ) {
        *state->status = RILL_LEX_UNCLOSED_STRING;
        return 0;
    }
    if ( !rutf8it_ok( &state->uit ) ) {
        *state->status = RILL_LEX_INVALID_UTF8;
        return 0;
    }
    if ( !rlexstate_range( &begin, state, RILL_LEXTOK_STRING ) ) {
        *state->status = RILL_LEX_UNDERLYING_ERROR;
        return 0;
    }

    rlexstate_step( state );
    return 1;
}

int rlex_cmt ( rlexstate * state ) {
    rlexstate begin = *state;
    while ( !rutf8it_done( &state->uit ) ) {
        rlexstate_step( state );
        if ( rutf8it_cdpt( &state->uit ) == RILL_LEX_CHAR_COMMENT_END )
            break;
    }

    if ( rutf8it_done( &state->uit ) ) {
        *state->status = RILL_LEX_UNCLOSED_COMMENT;
        return 0;
    }
    if ( !rutf8it_ok( &state->uit ) ) {
        *state->status = RILL_LEX_INVALID_UTF8;
        return 0;
    }
    if ( !rlexstate_range( &begin, state, RILL_LEX_UNCLOSED_COMMENT ) ) {
        *state->status = RILL_LEX_UNDERLYING_ERROR;
        return 0;
    }

    rlexstate_step( state );
    return 1;
}

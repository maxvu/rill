#include "config/rerr.h"
#include "rlex/rlexstate.h"
#include "rlex/rlextok.h"
#include "rlex/types.h"
#include "rval/rbuf.h"
#include "rval/rval.h"
#include "rval/rvec.h"
#include "util/rutf8.h"

int rlexstate_init ( rlexstate * state, rval * buf ) {
    if ( !state || !buf ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }
    if ( rval_type( buf ) != RVT_BUF ) {
        rerr_set( RILL_ERR_BADARG );
        return 0;
    }
    *state = ( rlexstate ) {
        .line = 1,
        .line_pos = 0,
        .pos = 0,
        .err = RILL_ERR_LEXOK,
        .buf = rbuf_get( buf ),
        .buf_end = rbuf_get( buf ) + rbuf_len( buf )
    };
    state->result = rnil();
    if ( !rvec_init( &state->result, RILL_LEXSTATE_RESULT_BUFFER_SIZE ) )
        return 0;
    return rutf8_peek( &state->peek, state->buf, state->buf_end );
}

void rlexstate_retire ( rlexstate * state ) {
    if ( !state )
        return;
    rval_release( &state->result );
}

int rlexstate_peek ( rlexstate * state ) {
    return state->peek.codepoint;
}

int rlexstate_step ( rlexstate * state ) {
    if ( !state ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }
    if ( RILL_IS_NEWLINE( state->peek.codepoint ) ) {
        state->line++;
        state->line_pos = 0;
    }
    state->pos += state->peek.n_bytes;
    if ( state->buf >= state->buf_end ) {
        state->err = RILL_ERR_LEXSTREAMEND;
        return 0;
    }
    return rutf8_peek( &state->peek, state->buf + state->pos, state->buf_end );
}

uint8_t * rlexstate_pos ( rlexstate * state ) {
    return state->buf + state->pos;
}

int rlexstate_eof ( rlexstate * state ) {
    return rlexstate_pos( state ) >= state->buf_end;
}

int rlexstate_ok ( rlexstate * state ) {
    return state->err != RILL_ERR_LEXOK;
}

int rlexstate_add_token ( rlexstate * state, uint8_t * begin, uint8_t type ) {
    if ( !state || !begin ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }
    rval token_buf = rnil();
    size_t n = state->buf + state->pos - begin;
    if ( !rbuf_init( &token_buf, n ) )
        return 0;
    if ( !rbuf_memcpy( &token_buf, begin, n ) ) {
        rval_release( &token_buf );
        return 0;
    }

    rval token = rnil();
    char ok = rlextok(
        &token,
        type,
        state->line,
        state->line_pos,
        &token_buf
    );
    ok &= rvec_push( &state->result, &token );

    rval_release( &token_buf );
    rval_release( &token );
    return ok;
}

#include "config/rerr.h"
#include "rlex/rlexstate.h"
#include "rlex/rlextok.h"
#include "rlex/types.h"
#include "rval/rbuf.h"
#include "rval/rval.h"
#include "rval/rvec.h"
#include "util/rutf8.h"

int rlexstate_init ( rlexstate * state, RVal * buf ) {
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
        .buf = rbuf_get( buf ),
        .buf_end = rbuf_get( buf ) + rbuf_len( buf )
    };
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
    state->buf += state->peek.n_bytes;
    if ( state->buf >= state->buf_end ) {
        rerr_set( RILL_ERR_LEXSTREAMEND );
        return 0;
    }
    return rutf8_peek( &state->peek, state->buf + state->pos, state->buf_end );
}

uint8_t * rlexstate_pos ( rlexstate * state ) {
    return state->buf + state->pos;
}

int rlexstate_done ( rlexstate * state ) {
    return rlexstate_pos( state ) >= state->buf_end;
}

int rlexstate_add_token ( rlexstate * state, uint8_t * begin ) {
    if ( !state || !begin ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }
    RVal token_buf = rnil();
    uint8_t * end = state->buf + state->pos;
    size_t n = end - begin;
    if ( !rbuf_init( &token_buf, n ) )
        return 0;
    if ( !rbuf_memcpy( &token_buf, begin, n ) ) {
        rval_release( &token_buf );
        return 0;
    }

    RVal token = rnil();
    char ok = rlextok(
        &token,
        RLXTOK_WHITESPACE,
        state->line,
        state->line_pos,
        &token_buf
    );
    ok &= rvec_push( &state->result, &token );

    rval_release( &token_buf );
    rval_release( &token );
    return ok;
}

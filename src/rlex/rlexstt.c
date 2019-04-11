#include "rlex/types.h"
#include "rlex/rlexstt.h"
#include "util/rutf8.h"

int rlexstt_init ( rlexstt * stt, RVal * buf ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    RILL_ASSERT_ISBUF( buf );
    *stt = rlexstt {
        .line = 1,
        .line_pos = 0,
        .buf = rbuf_get( buf ),
        .buf_len = rbuf_len( buf ),
        .pos = 0,
        .err = RILL_LEXSTT_OK,
        .result = rnil()
    };

    if ( !rutf8_peek( &stt->peek, stt->buf + stt->pos ) )
        return 0;
    if ( !rvec_init( &stt->result ) )
        return 0;

    return 1;
}

int rlexstt_retire ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    rval_release( &stt->result )
}

uint8_t * rlexstt_pos ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return stt->buf + stt->pos;
}

int rlexstt_ok ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return stt->err == RILL_LEXSTT_OK;
}

int rlexstt_step ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    if ( stt->pos >= stt->buf_len )
        return 0;
    stt->pos++;
    return rutf8_peek( &stt->peek, stt->buf + stt->pos );
}

int rlexstt_peek ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return stt->peek.codepoint;
}

int rlexstt_add ( rlexstt * stt, uint8_t * begin, uint8_t type ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    RILL_ASSERT_ARGNOTNULL( begin );

    RVal token_text = rnil();
    size_t n = stt->buf + stt->pos - begin;
    if ( !rbuf_init( &token_text, n ) )
        return 0;
    if ( !rbuf_memcpy( &token_text, begin, n ) ) {
        rval_release( &token_text );
        return 0;
    }

    RVal token = rnil();
    char ok = rlextok(
        &token,
        type,
        state->line,
        state->line_pos,
        &token_buf
    );
    ok &= rvec_push( &state->result, &token );

    rval_release( &token_text );
    rval_release( &token );
    return ok;
}

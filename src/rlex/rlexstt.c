#include "config/rerr.h"
#include "rlex/rlexstt.h"
#include "rlex/rlextok.h"
#include "rval/rbuf.h"
#include "rval/rval.h"
#include "rval/rvec.h"

int rlexstt_init ( rlexstt * stt, uint8_t * begin, uint8_t * end ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    RILL_ASSERT_ARGNOTNULL( begin );
    RILL_ASSERT_ARGNOTNULL( end );

    if ( !rlexit_init( &stt->end, begin, end ) ) {
        return 0;
        stt->status = RILL_LEX_UNDERLYING_ERROR;
    }
    if ( !rlexit_copy( &stt->begin, &stt->end ) ) {
        return 0;
        stt->status = RILL_LEX_UNDERLYING_ERROR;
    }
    stt->tokens = rvecq();
    if ( rval_isnil( &stt->tokens ) )
        return 0;
    stt->status = RILL_LEX_OK;
    return 1;
}

int rlexstt_retire ( rlexstt * stt ) {
    rval_release( &stt->tokens );
    return 1;
}

int rlexstt_step ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return rlexit_step( &stt->end );
}

int rlexstt_reset ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return rlexit_copy( &stt->begin, &stt->end );
}

int rlexstt_range ( rlexstt * stt, int type ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    char ok = 1;
    rval text = rbufq();
    rval token = rnil();

    if ( rval_isnil( &text ) )
        goto err;

    {
        uint8_t * a = rlexit_pos( &stt->begin );
        uint8_t * b = rlexit_pos( &stt->end );
        if ( a == b ) {
        }
        if ( !rbuf_memcpy( &text, a, b - a ) )
            goto err;
    }

    {
        size_t line = rlexit_line( &stt->begin );
        size_t offset = rlexit_offset( &stt->begin );
        if ( !rlextok( &token, type, line, offset, &text ) )
            goto err;
    }

    if ( !rvec_push( &stt->tokens, &token ) )
        goto err;

    if ( !rlexstt_reset( stt ) )
        goto err;

    goto done;

    err:
        stt->status = RILL_LEX_UNDERLYING_ERROR;
        ok = 0;
    done:
        rval_release( &text );
        rval_release( &token );
        return ok;
}

int rlexstt_ok ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return rlexit_ok( &stt->end ) && stt->status == RILL_LEX_OK;
}

int rlexstt_err ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return stt->status;
}

int rlexstt_done ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return !rlexstt_ok( stt ) || rlexit_done( &stt->end );
}

int rlexstt_cdpt ( rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return rlexit_cdpt( &stt->end );
}

int rlexstt_tokens ( rval * dst, rlexstt * stt ) {
    RILL_ASSERT_ARGNOTNULL( stt );
    return rval_copy( dst, &stt->tokens );
}

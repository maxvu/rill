#include "config/rerr.h"
#include "rlex/rlexchr.h"
#include "rlex/rlexit.h"
#include "rlex/rlextok.h"
#include "rval/rbuf.h"
#include "rval/rvec.h"

int rlexit_read ( rlexit * it ) {
    return rutf8_peek(
        &it->buffer.peek,
        it->buffer.bytes + it->buffer.pos,
        it->buffer.bytes + it->buffer.len
    );
}

int rlexit_init ( rlexit * it, rval * buf ) {
    RILL_ASSERT_ARGNOTNULL( it )
    RILL_ASSERT_ISBUF( buf )

    *it = ( rlexit ) {
        .line   = 1,
        .pos    = 0,
        .buffer = {
            .bytes = rbuf_get( buf ),
            .pos   = 0,
            .len   = rbuf_len( buf ),
            .peek  = {0}
        },
        .err    = RILL_LEXIT_OK,
        .result = rnil()
    };

    if ( !rvec_init( &it->result, RILL_LEXIT_DEFAULT_BUFFER_SIZE ) )
        return 0;
    rlexit_read( it );
    return 1;
}

int rlexit_retire ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    rval_release( &it->result );
    return 1;
}

unsigned int rlexit_geterr ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->err;
}

int rlexit_seterr ( rlexit * it, unsigned int err ) {
    RILL_ASSERT_ARGNOTNULL( it )
    it->err = err;
    return 1;
}

uint8_t * rlexit_buf ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->buffer.bytes;
}

int rlexit_ok ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->err == RILL_LEXIT_OK;
}

int rlexit_eof ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->buffer.pos < it->buffer.len;
}

int rlexit_done ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rlexit_eof( it ) || !rlexit_ok( it );
}

int rlexit_step ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    if ( rlexit_done( it ) )
        return 0;
    if ( rlexit_peek( it ) == RILL_LEX_CHAR_LINE_FEED ) {
        it->pos = 0;
        it->line++;
    }
    it->buffer.pos += it->buffer.peek.n_bytes;
    if ( !rlexit_read( it ) )
        return 0;
    return 1;
}

int rlexit_peek ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->buffer.peek.codepoint;
}

int rlexit_clip ( rlexit * it, uint8_t * from, uint8_t type ) {
    RILL_ASSERT_ARGNOTNULL( it )
    RILL_ASSERT_ARGNOTNULL( from )

    rval text = rnil();
    rval token = rnil();
    size_t n = it->buffer.bytes + it->buffer.pos - from;

    if ( !rbuf_init( &text, n ) )
        goto err;
    if ( !rbuf_memcpy( &text, from, n ) )
        goto err;
    if ( !rlextok( &token, type, it->line, it->pos, &text ) )
        goto err;
    if ( !rvec_push( &it->result, &token ) )
        goto err;

    rval_release( &text );
    rval_release( &token );
    return 0;

    err:
        rval_release( &text );
        rval_release( &token );
        return 0;
}

int rlexit_clipchar ( rlexit * it, uint8_t type ) {
    return rlexit_addchar( it, rlexit_peek( it ), type );
}

int rlexit_add ( rlexit * it, rval * text, uint8_t type ) {
    RILL_ASSERT_ARGNOTNULL( it )
    RILL_ASSERT_ARGNOTNULL( from )

    rval token = rnil();
    size_t n = it->buffer.bytes + it->buffer.pos - from;

    if ( !rlextok( &token, type, it->line, it->pos, &text ) )
        goto err;
    if ( !rvec_push( &it->result, &token ) )
        goto err;

    rval_release( &text );
    rval_release( &token );
    return 0;

    err:
        rval_release( &text );
        rval_release( &token );
        return 0;
}

int rlexit_addchar ( rlexit * it, int chr, uint8_t type ) {

}

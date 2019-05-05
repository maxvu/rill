#include "config/rerr.h"
#include "util/rutf8.h"
#include "util/rutf8it.h"

int rutf8it_init ( rutf8it * it, uint8_t * begin, uint8_t * end ) {
    RILL_ASSERT_ARGNOTNULL( it )
    RILL_ASSERT_ARGNOTNULL( begin )
    RILL_ASSERT_ARGNOTNULL( end )

    *it = ( rutf8it ) {
        .pos = 0,
        .cur = begin,
        .end = end,
        .err = RILL_ERR_UTFOK
    };

    return rutf8_peek( &it->peek, it->cur, it->end );
}

int rutf8it_copy ( rutf8it * dst, rutf8it * src ) {
    RILL_ASSERT_ARGNOTNULL( dst )
    RILL_ASSERT_ARGNOTNULL( src )
    *dst = *src;
    return 1;
}

int rutf8it_step ( rutf8it * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    if ( it->err != RILL_ERR_UTFOK )
        return 0;
    it->cur += it->peek.n_bytes;
    it->pos++;
    if ( !rutf8_peek( &it->peek, it->cur, it->end ) )
        return 0;
    return 1;
}

int rutf8it_err ( rutf8it * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->err;
}

int rutf8it_ok ( rutf8it * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->err == RILL_ERR_UTFOK;
}

int rutf8it_eof ( rutf8it * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->cur >= it->end;
}

int rutf8it_done ( rutf8it * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rutf8it_eof( it ) || !rutf8it_ok( it );
}

uint8_t * rutf8it_pos ( rutf8it * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->cur;
}

int rutf8it_cdpt ( rutf8it * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    if ( it->err != RILL_ERR_UTFOK )
        return 0;
    return it->peek.codepoint;
}

int rutf8it_nbytes ( rutf8it * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    if ( it->err != RILL_ERR_UTFOK )
        return 0;
    return it->peek.n_bytes;
}

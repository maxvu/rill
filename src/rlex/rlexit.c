#include "config/rerr.h"
#include "rlex/rlexit.h"
#include "rlex/rlexchr.h"
#include "util/rutf8it.h"

int rlexit_init ( rlexit * it, uint8_t * begin, uint8_t * end ) {
    RILL_ASSERT_ARGNOTNULL( it )
    RILL_ASSERT_ARGNOTNULL( begin )
    RILL_ASSERT_ARGNOTNULL( end )

    if ( !rutf8it_init( &it->uit, begin, end ) )
        return 0;
    it->lno = 1;
    it->lps = 0;
    return 1;
}

int rlexit_copy ( rlexit * dst, rlexit * src ) {
    RILL_ASSERT_ARGNOTNULL( dst )
    RILL_ASSERT_ARGNOTNULL( src )
    if ( !rutf8it_copy( &dst->uit, &src->uit ) )
        return 0;
    dst->lno = src->lno;
    dst->lps = src->lps;
    return 1;
}

int rlexit_retire ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return 1;
}

int rlexit_step ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    if ( rlexit_done( it ) )
        return 0;
    if ( rlexit_cdpt( it ) == RILL_LEX_CHAR_LINE_FEED ) {
        it->lno++;
        it->lps = 0;
    } else {
        it->lps++;
    }
    return rutf8it_step( &it->uit );
}

int rlexit_cdpt ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->uit.peek.codepoint;
}

uint8_t * rlexit_text ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rutf8it_pos( &it->uit );
}

size_t rlexit_pos ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->uit.pos;
}

size_t rlexit_lineno ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->lno;
}

int rlexit_linepos ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->lps;
}

int rlexit_err ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->uit.err;
}

int rlexit_ok ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rutf8it_ok( &it->uit );
}

int rlexit_eof ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rutf8it_eof( &it->uit );
}

int rlexit_done ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rutf8it_done( &it->uit );
}

int rlexit_range ( rval * token, rlexit * begin, rlexit * end, int type ) {

}

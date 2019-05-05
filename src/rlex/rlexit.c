#include "config/rerr.h"
#include "rlex/rlexchr.h"
#include "rlex/rlexit.h"
#include "util/rutf8it.h"

int rlexit_init ( rlexit * it, uint8_t * begin, uint8_t * end ) {
    RILL_ASSERT_ARGNOTNULL( it )
    RILL_ASSERT_ARGNOTNULL( begin )
    RILL_ASSERT_ARGNOTNULL( end )

    if ( !rutf8it_init( &it->uit, begin, end ) )
        return 0;
    it->line = 1;
    it->offset = 0;
    return 1;
}

int rlexit_copy ( rlexit * dst, rlexit * src ) {
    RILL_ASSERT_ARGNOTNULL( dst )
    RILL_ASSERT_ARGNOTNULL( src )

    if ( !rutf8it_copy( &dst->uit, &src->uit ) )
        return 0;
    dst->line = src->line;
    dst->offset = src->offset;
    return 1;
}

int rlexit_step ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    if ( rutf8it_done( &it->uit ) )
        return 0;
    if ( rutf8it_cdpt( &it->uit ) == RILL_LEX_CHAR_LINE_FEED ) {
        it->line++;
        it->offset = 0;
    } else {
        it->offset++;
    }

    return rutf8it_step( &it->uit );
}

int rlexit_ok ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rutf8it_ok( &it->uit );
}

int rlexit_done ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rutf8it_done( &it->uit );
}

int rlexit_cdpt ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rutf8it_cdpt( &it->uit );
}

uint8_t * rlexit_pos ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return rutf8it_pos( &it->uit );
}

size_t rlexit_line ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->line;
}

size_t rlexit_offset ( rlexit * it ) {
    RILL_ASSERT_ARGNOTNULL( it )
    return it->offset;
}

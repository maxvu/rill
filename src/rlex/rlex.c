#include "config/arch.h"
#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rlex/chars.h"
#include "rlex/types.h"
#include "rlex/rlexstate.h"
#include "rval/dump.h"
#include "rval/ruxx.h"
#include "rval/rvec.h"
#include "util/rutf8.h"

#include <stdio.h>

int rlex_ws ( rlexstt * stt ) {
    uint8_t * begin = rlexstt_pos( stt );

    while ( rlexstt_step( stt ) && rlexchr_ws( rlexstt_peek( stt ) ) )
        {}

    if ( !rlexstt_ok( stt ) )
        return 0;

    return rlexstt_add( stt, begin, RILL_LEXTOK_WHITESPACE );
}

int rlex_ws ( rlexstt * stt ) {
    uint8_t * begin = rlexstt_pos( stt );

    while ( rlexstt_step( stt ) && rlexchr_idbody( rlexstt_peek( stt ) ) )
        {}

    if ( !rlexstt_ok( stt ) )
        return 0;

    return rlexstt_add( stt, begin, RILL_LEXTOK_IDENTIFIER );
}

int rlex_identifier ( rlexstate * state ) {
    uint8_t * begin = rlexstate_pos( state );

    while ( rlex_ischr_idbody( rlexstate_peek( state ) ) ) {
        rlexstate_step( state );
    }

    return rlexstate_add_token( state, begin, RLXTOK_IDENTIFIER );
}

int rlex_str ( rlexstate * state );
int rlex_comment ( rlexstate * state );

int rlex_numeric ( rlexstate * stt );

int rlex ( RVal * dst, RVal * lexbuf ) {
    RILL_ASSERT_ARGNOTNULL( dst );
    RILL_ASSERT_ISBUF( lexbuf );

    rlexstt state;
    if ( !rlexstt_init( &stt, lexbuf ) )
        return 0;

    int c;

    begin:
        c = rlexstt_peek( stt );

        if ( rlexchr_ws( c ) ) {
            if ( rlex_ws( stt ) )
                goto step;
            goto err;
        } else if ( rlexchr_strdelim( c ) ) {
            if ( rlex_str( stt ) )
                goto step;
            goto err;
        } else if ( rlexchr_numopen( c ) ) {
            if ( rlex_num( stt ) )
                goto step;
            goto err;
        }

        switch ( c ) {
            case RILL_LEX_CHAR_ENUM_BEGIN:
            case RILL_LEX_CHAR_ENUM_END:

            case RILL_LEX_CHAR_QUOTE_BEGIN:
            case RILL_LEX_CHAR_QUOTE_END:
            case RILL_LEX_CHAR_COMMENT_BEGIN:
            case RILL_LEX_CHAR_COMMENT_END:
            case RILL_LEX_CHAR_COMPILE_MODE_BEGIN:
            case RILL_LEX_CHAR_COMPILE_MODE_END:
        }

        if ( rlexchr_idopen( c ) ) {
            if ( !rlex_id( &stt ) )
                goto err;
        } else {
            stt.err = RILL_LEXSTT_UNEXPECTED_CHAR;
            goto err;
        }

        step:
            if ( !rlexstt_ok( &stt ) )
                goto err;
            goto done;

        done:
            if ( !rval_copy( dst, &stt.result ) )
                goto err;
            rlexstt_retire( &stt );
            return 1;

        err:
            rlexstt_retire( &stt );
            return 0;

}

int rlex_dump ( RVal * lexbuf ) {
    RVal result = rnil();
    if ( !rlex( &result, lexbuf ) ) {
        printf( "lex failed with code %x\n", rerr_get() );
        rerr_clear();
    }
    size_t n = rvec_len( &result );
    for ( size_t i = 0; i < n; i++ )
        rlextok_dump( rvec_get( &result, i ) );
    rval_release( &result );
}

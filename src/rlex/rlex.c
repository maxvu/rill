#include "config/arch.h"
#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rlex/rlexchr.h"
#include "rlex/types.h"
#include "rlex/rlextok.h"
#include "rlex/rlexstt.h"
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

int rlex_id ( rlexstt * stt ) {
    uint8_t * begin = rlexstt_pos( stt );
    while ( rlexstt_step( stt ) && rlexchr_idbody( rlexstt_peek( stt ) ) )
        {}
    if ( !rlexstt_ok( stt ) )
        return 0;
    return rlexstt_add( stt, begin, RILL_LEXTOK_IDENTIFIER );
}

int rlex_stresc ( rlexstt * stt );
// int rlex_stresc ( rlexstt * stt ) {
//     int c;
//
//     rlexstt_step( stt );
//     switch ( rlexstt_peek( stt ) ) {
//         case RILL_LEX_CHAR_X_LOWER:
//             break;
//         case RILL_LEX_CHAR_B_LOWER:
//             break;
//         case RILL_LEX_CHAR_V_LOWER:
//             break;
//         case RILL_LEX_CHAR_T_LOWER:
//             break;
//         case RILL_LEX_CHAR_F_LOWER:
//             break;
//         case RILL_LEX_CHAR_N_LOWER:
//             break;
//         case RILL_LEX_CHAR_R_LOWER:
//             break;
//     }
// }

int rlex_str ( rlexstt * stt ) {
    int c;

    int delim = rlexstt_peek( stt );
    rlexstt_step( stt );
    uint8_t * begin = rlexstt_pos( stt );

    while ( rlexstt_step( stt ) ) {
        c = rlexstt_peek( stt );
        if ( c == delim )
            break;
        else if ( c == RILL_LEX_CHAR_STRING_ESCAPE )
            if ( !rlex_stresc( stt ) )
                return 0;
    }
    if ( !rlexstt_add( stt, begin, RILL_LEXTOK_STRING ) )
        return 0;
    if ( rlexstt_eof( stt ) ) {
        rerr_set( RILL_LEXSTT_UNCLOSED_STRING );
        return 0;
    }
    rlexstt_step( stt );
    return 1;
}

int rlex_comment ( rlexstt * stt );

int rlex_num ( rlexstt * stt ) {
    rlexstt_step( stt );
    return 1;
}

int rlex_single ( rlexstt * stt, int type ) {
    rlexstt_step( stt );
    return 1;
}

int rlex ( RVal * dst, RVal * lexbuf ) {
    RILL_ASSERT_ARGNOTNULL( dst );
    RILL_ASSERT_ISBUF( lexbuf );

    printf( "rlex() \n");

    rlexstt stt;
    if ( !rlexstt_init( &stt, lexbuf ) )
        return 0;

    printf( "  init stt \n");

    int c;

    step:

    printf( "  step \n");

    if ( rlexstt_done( &stt ) )
        goto done;

    c = rlexstt_peek( &stt );

    printf( "  peek char %d \n", c);

    if ( rlexchr_ws( c ) ) {
        printf( "  is ws \n");
        if ( !rlex_ws( &stt ) )
            goto err;
        goto step;
    } else if ( rlexchr_strdelim( c ) ) {
        printf( "  is str \n");
        if ( !rlex_str( &stt ) )
            goto err;
        goto step;
    } else if ( rlexchr_numopen( c ) ) {
        printf( "  is num \n");
        if ( !rlex_num( &stt ) )
            goto err;
        goto step;
    }

    switch ( c ) {
        case RILL_LEX_CHAR_ENUM_BEGIN:
            if ( !rlex_single( &stt, RILL_LEXTOK_ENUM_OPEN ) )
                goto err;
            goto step;
            break;
        case RILL_LEX_CHAR_ENUM_END:
            if ( !rlex_single( &stt, RILL_LEXTOK_ENUM_CLOSE ) )
                goto err;
            goto step;
            break;
        case RILL_LEX_CHAR_QUOTE_BEGIN:
            if ( !rlex_single( &stt, RILL_LEXTOK_QUOTE_OPEN ) )
                goto err;
            goto step;
            break;
        case RILL_LEX_CHAR_QUOTE_END:
            if ( !rlex_single( &stt, RILL_LEXTOK_QUOTE_CLOSE ) )
                goto err;
            goto step;
            break;
        case RILL_LEX_CHAR_COMMENT_BEGIN:
            if ( !rlex_single( &stt, RILL_LEXTOK_COMMENT_OPEN ) )
                goto err;
            goto step;
            break;
        case RILL_LEX_CHAR_COMMENT_END:
            if ( !rlex_single( &stt, RILL_LEXTOK_COMMENT_CLOSE ) )
                goto err;
            goto step;
            break;
        case RILL_LEX_CHAR_COMPILE_MODE_BEGIN:
            if ( !rlex_single( &stt, RILL_LEXTOK_COMPILE_OPEN ) )
                goto err;
            goto step;
            break;
        case RILL_LEX_CHAR_COMPILE_MODE_END:
            if ( !rlex_single( &stt, RILL_LEXTOK_COMPILE_CLOSE ) )
                goto err;
            goto step;
            break;
    }

    if ( rlexchr_idopen( c ) ) {
        if ( !rlex_id( &stt ) )
            goto err;
        goto step;
    }

    stt.err = RILL_LEXSTT_UNEXPECTED_CHAR;
    goto err;

    done:
        if ( !rval_copy( dst, &stt.result ) )
            goto err;
        rlexstt_retire( &stt );
        return 1;

    err:
        rerr_set( stt.err );
        rlexstt_retire( &stt );
        return 0;

}

int rlex_dump ( RVal * lexbuf ) {
    RVal result = rnil();
    int code = rlex( &result, lexbuf );
    size_t n = rvec_len( &result );
    for ( size_t i = 0; i < n; i++ )
        rlextok_dump( rvec_get( &result, i ) );
    rval_release( &result );
    if ( !code ) {
        printf( "lex failed with code %lx\n", rerr_get() );
        rerr_clear();
        return 0;
    }
    return 1;
}

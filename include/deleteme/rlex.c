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

int rlex_whitespace ( rlexstate * state ) {
    uint8_t * begin = rlexstate_pos( state );
    int c;

    peek:
    c = rlexstate_peek( state );

    if ( !rlex_ischr_whitespace( c ) )
        goto done;
    if ( !rlexstate_step( state ) )
        goto done;
    goto peek;

    done:
    if ( !rlexstate_ok( state ) )
        return 0;
    return rlexstate_add_token( state, begin, RLXTOK_WHITESPACE );
}

int rlex_identifier ( rlexstate * state ) {
    uint8_t * begin = rlexstate_pos( state );

    while ( rlex_ischr_idbody( rlexstate_peek( state ) ) ) {
        rlexstate_step( state );
    }

    return rlexstate_add_token( state, begin, RLXTOK_IDENTIFIER );
}

int rlex_string ( rlexstate * state );
int rlex_comment ( rlexstate * state );
int rlex_numeric ( rlexstate * state );

int rlex ( RVal * dst, RVal * lexbuf ) {
    if ( !dst || !lexbuf ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }

    rlexstate state;
    if ( !rlexstate_init( &state, lexbuf ) )
        return 0;

    int c;
    while ( !rlexstate_eof( &state ) ) {
        c = rlexstate_peek( &state );

        if ( rlex_ischr_whitespace( c ) ) {
            if ( !rlex_whitespace( &state ) )
                goto done;
        } else if ( rlex_ischr_idopen( c ) ) {
            if ( !rlex_identifier( &state ) )
                goto done;
        } else {
            // can you even get here?
            printf( "what do with char %x?\n", *(state.buf + state.pos));
        }
    }

    done:
        if ( !rlexstate_ok( &state ) )
            goto error;
        rerr_clear();
        if ( !rval_copy( dst, &state.result ) )
            goto error;
        rlexstate_retire( &state );
        return 1;


    error:
        rlexstate_retire( &state );
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

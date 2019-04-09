#include "config/arch.h"
#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rlex/chars.h"
#include "rlex/types.h"
#include "rlex/rlexstate.h"
#include "rval/ruxx.h"
#include "rval/rvec.h"
#include "util/rutf8.h"

int rlex_whitespace ( rlexstate * state ) {
    uint8_t * begin = rlexstate_pos( state );

    while ( rlex_ischr_whitespace( rlexstate_peek( state ) ) ) {
        if ( !rlexstate_step( state ) )
            return 0;
    }

    return rlexstate_add_token( state, begin );
}

int rlex_identifier ( rlexstate * state ) {
    uint8_t * begin = rlexstate_pos( state );

    while ( rlex_ischr_idbody( rlexstate_peek( state ) ) ) {
        if ( !rlexstate_step( state ) )
            return 0;
    }

    return rlexstate_add_token( state, begin );
}

int rlex_string ( rlexstate * state );
int rlex_comment ( rlexstate * state );
int rlex_numeric ( rlexstate * state );

int rlex ( RVal * dst, RVal * lexbuf ) {
    if ( !dst || !lexbuf ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }

    RVal result = rnil();
    if ( !rvec_init( &result, RILL_LEX_RESULT_BUFFER_SIZE ) )
        return 0;

    rlexstate state;
    if ( !rlexstate_init( &state, lexbuf ) )
        return 0;

    int c;
    while ( !rlexstate_done( &state ) ) {
        c = rlexstate_peek( &state );

        if ( rlex_ischr_whitespace( c ) && !rlex_whitespace( &state ) ) {
            goto done;
        } else if ( rlex_ischr_idopen( c ) && !rlex_identifier( &state ) ) {
            goto done;
        } else {
            // can you even get here?
        }
    }

    done:
        if ( rerr_get() != RILL_ERR_LEXOK )
            goto error;
        if ( !rval_copy( dst, &result ) )
            goto error;
        rlexstate_retire( &state );
        return 1;


    error:
        rval_release( &result );
        return 0;
}

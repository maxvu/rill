#include "config/arch.h"
#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rlex/rlextok.h"
#include "rlex/chars.h"
#include "rlex/types.h"
#include "rval/rbuf.h"
#include "rval/ruxx.h"
#include "rval/rvec.h"
#include "util/rutf8.h"

#define RILL_LEX_RESULT_BUFFER_SIZE 128

int is_str_open ( int c ) {
    // switch ( c ) {
    //     case RILL_LEX_CHAR_STR_OPEN1:
    //     case RILL_LEX_CHAR_STR_OPEN2:
    //         return 1;
    //         break;
    // }
    // return 0;
}

/*
    [^-][^:reserved:]
*/

int is_id_char ( int c ) {
    // if ( is_space( c ) )
    //     return 0;
    // switch ( c ) {
    //     case RILL_LEX_CHAR_LIST_OPEN:
    //     case RILL_LEX_CHAR_LIST_CLOSE:
    //     case RILL_LEX_CHAR_HASH_OPEN:
    //     case RILL_LEX_CHAR_HASH_CLOSE:
    //     case RILL_LEX_CHAR_QUOT_OPEN:
    //     case RILL_LEX_CHAR_QUOT_CLOSE:
    //     case RILL_LEX_CHAR_COMP_OPEN:
    //     case RILL_LEX_CHAR_COMP_CLOSE:
    //         return 0;
    //         break;
    // }
    // return 1;
}

int is_id_open_char ( int c ) {
    // if ( !is_id_char( c ) )
    //     return 0;
    // switch ( c ) {
    //     case RILL_LEX_CHAR_NUM_NEG:
    //         return 0;
    //         break;
    // }
    // return 1;
}

/*
    [-]?[0-9]+([.][0-9]+)?(e[0-9]+)?
*/

int is_num_open_char ( int c ) {
    switch ( c ) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case RILL_LEX_CHAR_NUM_DEC:
        case RILL_LEX_CHAR_NUM_NEG:
            return 1;
            break;
    }
    return 0;
}

int is_num_char ( int c ) {
    switch ( c ) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case RILL_LEX_CHAR_NUM_DEC:
        case RILL_LEX_CHAR_NUM_HEX:
        case RILL_LEX_CHAR_NUM_POW:
            return 1;
            break;
    }
    return 0;
}

/*
    parse hex nibble
    parse hex number
    parse single escaped string character
*/

typedef struct rlexstate {
    size_t line;          // line number
    size_t line_pos;      // position in line
    size_t pos;           // position in buffer
    RUTF8Peek peek;       // UTF-8 cursor result
    uint8_t * buf;     // buffer begin
    uint8_t * buf_end; // buffer end
    RVal result;          // rvec of rlextok's
} rlexstate;

int rlexstate_init ( rlexstate * state, RVal * buf ) {
    if ( !state || !buf ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }
    if ( rval_type( buf ) != RVT_BUF ) {
        rerr_set( RILL_ERR_BADARG );
        return 0;
    }
    *state = ( rlexstate ) {
        .line = 1,
        .line_pos = 0,
        .pos = 0,
        .buf = rbuf_get( buf ),
        .buf_end = rbuf_get( buf ) + rbuf_len( buf )
    };
    return rutf8_peek( &state->peek, state->buf, state->buf_end );
}

void rlexstate_retire ( rlexstate * state ) {
    if ( !state )
        return;
    rval_release( &state->result );
}

int rlexstate_peek ( rlexstate * state ) {
    return state->peek.codepoint;
}

uint8_t * rlexstate_pos ( rlexstate * state ) {
    return state->buf + state->pos;
}

int rlexstate_step ( rlexstate * state ) {
    if ( !state ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }
    if ( RILL_IS_NEWLINE( state->peek.codepoint ) ) {
        state->line++;
        state->line_pos = 0;
    }
    state->buf += state->peek.n_bytes;
    if ( state->buf >= state->buf_end ) {
        rerr_set( RILL_ERR_LEXSTREAMEND );
        return 0;
    }
    return rutf8_peek( &state->peek, state->buf + state->pos, state->buf_end );
}

int rlexstate_add_token ( rlexstate * state, uint8_t * begin ) {
    if ( !state || !begin ) {
        rerr_set( RILL_ERR_NULLARG );
        return 0;
    }
    RVal token_buf = rnil();
    uint8_t * end = state->buf + state->pos;
    size_t n = end - begin;
    if ( !rbuf_init( &token_buf, n ) )
        return 0;
    if ( !rbuf_memcpy( &token_buf, begin, n ) ) {
        rval_release( &token_buf );
        return 0;
    }

    RVal token = rnil();
    char ok = rlextok(
        &token,
        RLXTOK_WHITESPACE,
        state->line,
        state->line_pos,
        &token_buf
    );
    ok &= rvec_push( &state->result, &token );

    rval_release( &token_buf );
    rval_release( &token );
    return ok;
}

int rlex_hexnibble ( rlexstate * state );

int rlex_whitespace ( rlexstate * state ) {
    uint8_t * begin = rlexstate_pos( state );

    peek:
        switch ( rlexstate_peek( state ) ) {
            case 0x0008:
            case 0x0009:
            case 0x000A:
            case 0x000B:
            case 0x000C:
            case 0x000D:
            case 0x0020:
            case 0x00A0:
            case 0x2002:
            case 0x2003:
            case 0x2004:
            case 0x2005:
            case 0x2006:
            case 0x2007:
            case 0x2008:
            case 0x2009:
            case 0x200A:
            case 0x200B:
            case 0x202F:
            case 0x205F:
            case 0x3000:
            case 0xFEFF:
            case 0xE0020:
                if ( !rlexstate_step( state ) )
                    return 0;
                goto peek;
                break;
            default:
                goto done;
                break;
        }

    done:
        return rlexstate_add_token( state, begin );
}

int rlex_identifier ( rlexstate * state );
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

    if ( !rval_copy( dst, &result ) )
        goto error;

    rlexstate_retire( &state );

    return 1;

    error:
        rval_release( &result );
        return 0;
}

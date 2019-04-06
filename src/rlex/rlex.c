#include "rlex/rlex.h"
#include "rlex/chars.h"
#include "rlex/types.h"
#include "rlex/errors.h"
#include "rval/ruxx.h"
#include "rval/rbuf.h"
#include "rval/rvec.h"


#define RILL_LEX_UNKNOWN_UNIT_NAME "<\?\?\?>"

int is_str_open ( int c ) {
    switch ( c ) {
        case RILL_LEX_CHAR_STR_OPEN1:
        case RILL_LEX_CHAR_STR_OPEN2:
            return 1;
            break;
    }
    return 0;
}

int is_space ( int c ) {
    switch ( c ) {
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
            return 1;
            break;
    }
    return 0;
}

/*
    [^-][^:reserved:]
*/

int is_id_char ( int c ) {
    if ( is_space( c ) )
        return 0;
    switch ( c ) {
        case RILL_LEX_CHAR_LIST_OPEN:
        case RILL_LEX_CHAR_LIST_CLOSE:
        case RILL_LEX_CHAR_HASH_OPEN:
        case RILL_LEX_CHAR_HASH_CLOSE:
        case RILL_LEX_CHAR_QUOT_OPEN:
        case RILL_LEX_CHAR_QUOT_CLOSE:
        case RILL_LEX_CHAR_COMP_OPEN:
        case RILL_LEX_CHAR_COMP_CLOSE:
            return 0;
            break;
    }
    return 1;
}

int is_id_open_char ( int c ) {
    if ( !is_id_char( c ) )
        return 0;
    switch ( c ) {
        case RILL_LEX_CHAR_NUM_NEG:
            return 0;
            break;
    }
    return 1;
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

RVal rlexer ( RVal * unit_name ) {
    RVal lexer = rnil();
    RVal curr = rnil();

    if ( !rvec_init( &lexer, 4 ) )
        goto error;

    // Set unit name name.
    if ( !unit_name || rval_type( unit_name ) != RVT_BUF ) {
        // If no unit name provided, supply a dummy one.
        if ( !rbuf_strcpy( &curr, RILL_LEX_UNKNOWN_UNIT_NAME ) )
            goto error;
        if ( !rvec_push( &lexer, &curr ) )
            goto error;
        rval_release( &curr );
    } else {
        // Otherwise, copy the one provided.
        if ( !rvec_push( &lexer, unit_name ) )
            goto error;
    }

    // Set line to 1.
    ruxx_set( &curr, 1 );
    if ( !rvec_push( &lexer, &curr ) )
        goto error;

    // Set position to 0.
    ruxx_set( &curr, 0 );
    if ( !rvec_push( &lexer, &curr ) )
        goto error;

    // Initialize output tokens vector.
    curr = rvec();
    if ( rval_type( &curr ) != RVT_VEC )
        goto error;
    if ( !rvec_push( &lexer, &curr ) )
        goto error;

    return lexer;

    error:
        rval_release( &curr );
        rval_release( &lexer );
        return lexer;
}

int rlexer_lex ( RVal * lexer );
int rlexer_tokens ( RVal * lexer );

RVal rlexer_token ();
//
// RVal * rlexer_token_type ( RVal * token ) {
//     if ( rvec_len( token ) != 4 )
//         return NULL;
//     return rvec_get( token, 0 );
// }
//
// RVal * rlexer_token_line ( RVal * token ) {
//     if ( rvec_len( token ) != 4 )
//         return NULL;
//     return rvec_get( token, 1 );
// }
//
// RVal * rlexer_token_pos  ( RVal * token ) {
//     if ( rvec_len( token ) != 4 )
//         return NULL;
//     return rvec_get( token, 2 );
// }
//
// RVal * rlexer_token_text  ( RVal * token ) {
//     if ( rvec_len( token ) != 4 )
//         return NULL;
//     return rvec_get( token, 3 );
// }

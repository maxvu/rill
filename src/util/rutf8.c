#include "util/rutf8.h"

const uint8_t MASK_MSB[] = {
    0b00000000,
    0b10000000,
    0b11000000,
    0b11100000,
    0b11110000,
    0b11111000,
};

const uint8_t IS_SINGLE_BYTE ( uint8_t * byt ) {
    return ( *byt & MASK_MSB[1] ) == 0;
}
const uint8_t IS_CONTIN_BYTE ( uint8_t * byt ) {
    return ( *byt & MASK_MSB[2] ) == MASK_MSB[1];
}
const uint8_t IS_DOUBLE_BYTE ( uint8_t * byt ) {
    return ( *byt & MASK_MSB[3] ) == MASK_MSB[2];
}
const uint8_t IS_TRIPLE_BYTE ( uint8_t * byt ) {
    return ( *byt & MASK_MSB[4] ) == MASK_MSB[3];
}
const uint8_t IS_QUADRU_BYTE ( uint8_t * byt ) {
    return ( *byt & MASK_MSB[5] ) == MASK_MSB[4];
}

uint32_t GET_SINGLE_VAL( uint8_t * byt ) {
    return *byt & ~MASK_MSB[1];
}
uint32_t GET_CONTIN_VAL( uint8_t * byt ) {
    return *byt & ~MASK_MSB[2];
}
uint32_t GET_DOUBLE_VAL( uint8_t * byt ) {
    return *byt & ~MASK_MSB[3];
}
uint32_t GET_TRIPLE_VAL( uint8_t * byt ) {
    return *byt & ~MASK_MSB[4];
}
uint32_t GET_QUADRU_VAL( uint8_t * byt ) {
    return *byt & ~MASK_MSB[5];
}

uint8_t rutf8_continue_byte ( RUTF8Peek * peek, uint8_t * cb ) {
    if ( !IS_CONTIN_BYTE( cb ) ) {
        peek->error = RUTF8_EARLY_TRUNCATION;
        return 0;
    }
    peek->codepoint = ( peek->codepoint << 6 ) & GET_CONTIN_VAL( cb );
    return 1;
}

int rutf8_peek ( RUTF8Peek * peek, uint8_t * pos, uint8_t * end ) {
    if ( !peek )
        return 0;
    *peek = ( RUTF8Peek ) {
        .n_bytes = 0,
        .error = RUTF8_OK,
        .codepoint = 0
    };
    if ( !pos || !end ) {
        peek->error = RUTF8_PASSED_NULLPTR;
        return 0;
    }
    if ( pos == end ) {
        return 0;
    }
    if ( IS_SINGLE_BYTE( pos ) ) {
        peek->n_bytes = 1;
        peek->codepoint = GET_SINGLE_VAL( pos );
        return 1;
    } else if ( IS_DOUBLE_BYTE( pos ) ) {
        peek->n_bytes = 2;
        if ( end - pos < 2 ) {
            peek->error = RUTF8_EOF_TRUNCATION;
            return 0;
        }
        peek->codepoint = GET_DOUBLE_VAL( pos );
        if ( !rutf8_continue_byte( peek, ++pos ) )
            return 0;
    } else if ( IS_TRIPLE_BYTE( pos ) ) {
        peek->n_bytes = 3;
        if ( end - pos < 3 ) {
            peek->error = RUTF8_EOF_TRUNCATION;
            return 0;
        }
        peek->codepoint = GET_TRIPLE_VAL( pos );
        if ( !rutf8_continue_byte( peek, ++pos ) )
            return 0;
        if ( !rutf8_continue_byte( peek, ++pos ) )
            return 0;
    } else if ( IS_QUADRU_BYTE( pos ) ) {
        peek->n_bytes = 4;
        if ( end - pos < 4 ) {
            peek->error = RUTF8_EOF_TRUNCATION;
            return 0;
        }
        peek->codepoint = GET_QUADRU_VAL( pos );
        if ( !rutf8_continue_byte( peek, ++pos ) )
            return 0;
        if ( !rutf8_continue_byte( peek, ++pos ) )
            return 0;
        if ( !rutf8_continue_byte( peek, ++pos ) )
            return 0;
    } else {
        peek->error = RUTF8_INVALID_BYTE;
        return 0;
    }
    return 1;
}

int rutf8_scan ( RUTF8Scan * scan, uint8_t * pos, uint8_t * end ) {
    if ( !scan | !pos | !end )
        return 0;
    *scan = ( RUTF8Scan ) {
        .length = 0,
        .error = RUTF8_OK
    };
    RUTF8Peek peek;
    rutf8_peek ( &peek, pos, end );
    while ( peek.error == RUTF8_OK && pos < end ) {
        pos += peek.n_bytes;
        scan->length++;
        rutf8_peek( &peek, pos, end );
    }
    if ( peek.error != RUTF8_OK ) {
        scan->error = peek.error;
        return 0;
    }
    return 1;
}

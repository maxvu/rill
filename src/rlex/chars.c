#include "rlex/chars.h"

int rlex_ischr_whitespace ( int c ) {
    switch ( c ) {
        case RILL_LEX_CHAR_BACKSPACE:
        case RILL_LEX_CHAR_TAB:
        case RILL_LEX_CHAR_LINE_FEED:
        case RILL_LEX_CHAR_LINE_TABE:
        case RILL_LEX_CHAR_FORM_FEED:
        case RILL_LEX_CHAR_CARRIAGE_RETURN:
        case RILL_LEX_CHAR_SPACE:
        case RILL_LEX_CHAR_NEXT_LINE:
        case RILL_LEX_CHAR_NONBREAKING_SPACE:
        case RILL_LEX_CHAR_OGHAM_SPACE:
        case RILL_LEX_CHAR_MONGOLIAN_VOWEL_SEPARATOR:
        case RILL_LEX_CHAR_EN_QUAD:
        case RILL_LEX_CHAR_EM_QUAD:
        case RILL_LEX_CHAR_EN_SPACE:
        case RILL_LEX_CHAR_EM_SPACE:
        case RILL_LEX_CHAR_THREE_PER_SPACE_EM:
        case RILL_LEX_CHAR_FOUR_PER_SPACE_EM:
        case RILL_LEX_CHAR_SIX_PER_SPACE_EM:
        case RILL_LEX_CHAR_FIGURE_SPACE:
        case RILL_LEX_CHAR_PUNCTUATION_SPACE:
        case RILL_LEX_CHAR_THIN_SPACE:
        case RILL_LEX_CHAR_HAIR_SPACE:
        case RILL_LEX_CHAR_ZERO_WIDTH_SPACE:
        case RILL_LEX_CHAR_ZERO_WIDTH_NON_JOINER:
        case RILL_LEX_CHAR_ZERO_WIDTH_JOINER:
        case RILL_LEX_CHAR_LINE_SEPARATOR:
        case RILL_LEX_CHAR_PARAGRAPH_SEPARATOR:
        case RILL_LEX_CHAR_NARROW_NONBREAKING_SPACE:
        case RILL_LEX_CHAR_MEDIUM_MATHEMATICAL_SPACE:
        case RILL_LEX_CHAR_WORD_JOINER:
        case RILL_LEX_CHAR_IDEOGRAPHIC_SPACE:
        case RILL_LEX_CHAR_BOM: /// TODO: ???
            return 1;
            break;
    }
    return 0;
}

int rlex_ischr_stringdelim ( int c ) {
    switch ( c ) {
        case RILL_LEX_CHAR_QUOTEMARK_SINGLE:
        case RILL_LEX_CHAR_QUOTEMARK_DOUBLE:
            return 1;
            break;
    }
    return 0;
}

int rlex_ischr_idopen ( int c ) {
    if ( !rlex_ischr_idbody( c ) )
        return 0;
    switch ( c ) {
        case RILL_LEX_CHAR_NUMERIC_NEGATOR:
            return 0;
            break;
    }
    return 1;
}

int rlex_ischr_idbody ( int c ) {
    if ( rlex_ischr_whitespace( c ) )
        return 0;
    if ( rlex_ischr_stringdelim( c ) )
        return 0;
    switch ( c ) {
        case RILL_LEX_CHAR_ENUM_BEGIN:
        case RILL_LEX_CHAR_ENUM_END:
        case RILL_LEX_CHAR_QUOTE_BEGIN:
        case RILL_LEX_CHAR_QUOTE_END:
        case RILL_LEX_CHAR_COMMENT_BEGIN:
        case RILL_LEX_CHAR_COMMENT_END:
        case RILL_LEX_CHAR_COMPILE_MODE_BEGIN:
        case RILL_LEX_CHAR_COMPILE_MODE_END:
        case RILL_LEX_CHAR_STRING_DELIM_SINGLE:
        case RILL_LEX_CHAR_STRING_DELIM_DOUBLE:
            return 0;
            break;
    }
    return 1;
}

int rlex_ischr_numopen ( int c ) {
    switch ( c ) {
        case RILL_LEX_CHAR_NUMERIC_NEGATOR:
        case RILL_LEX_CHAR_NUMERIC_DECIMAL:
        case RILL_LEX_CHAR_ZERO:
        case RILL_LEX_CHAR_ONE:
        case RILL_LEX_CHAR_TWO:
        case RILL_LEX_CHAR_THREE:
        case RILL_LEX_CHAR_FOUR:
        case RILL_LEX_CHAR_FIVE:
        case RILL_LEX_CHAR_SIX:
        case RILL_LEX_CHAR_SEVEN:
        case RILL_LEX_CHAR_EIGHT:
        case RILL_LEX_CHAR_NINE:
            return 1;
            break;
    }
    return 0;
}

int rlex_ischr_numbody ( int c ) {
    if ( rlex_ischr_numopen( c ) )
        return 1;
    switch ( c ) {
        case RILL_LEX_CHAR_EXPONENT_MARK_LOWER:
        case RILL_LEX_CHAR_EXPONENT_MARK_UPPER:
        case RILL_LEX_CHAR_HEX_ESCAPE_LOWER:
        case RILL_LEX_CHAR_HEX_ESCAPE_UPPER:
            return 1;
    }
    return 0;
}

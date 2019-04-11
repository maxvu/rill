#ifndef RILL_RLEX_CHARS
#define RILL_RLEX_CHARS

/* whitespace characters */
#define RILL_LEX_CHAR_BACKSPACE                  0x0008
#define RILL_LEX_CHAR_TAB                        0x0009
#define RILL_LEX_CHAR_LINE_FEED                  0x000A
#define RILL_LEX_CHAR_LINE_TABE                  0x000B
#define RILL_LEX_CHAR_FORM_FEED                  0x000C
#define RILL_LEX_CHAR_CARRIAGE_RETURN            0x000D
#define RILL_LEX_CHAR_SPACE                      0x0020
#define RILL_LEX_CHAR_NEXT_LINE                  0x0085
#define RILL_LEX_CHAR_NONBREAKING_SPACE          0x00A0
#define RILL_LEX_CHAR_OGHAM_SPACE                0x1680
#define RILL_LEX_CHAR_MONGOLIAN_VOWEL_SEPARATOR  0x180E
#define RILL_LEX_CHAR_EN_QUAD                    0x2000
#define RILL_LEX_CHAR_EM_QUAD                    0x2001
#define RILL_LEX_CHAR_EN_SPACE                   0x2002
#define RILL_LEX_CHAR_EM_SPACE                   0x2003
#define RILL_LEX_CHAR_THREE_PER_SPACE_EM         0x2004
#define RILL_LEX_CHAR_FOUR_PER_SPACE_EM          0x2005
#define RILL_LEX_CHAR_SIX_PER_SPACE_EM           0x2006
#define RILL_LEX_CHAR_FIGURE_SPACE               0x2007
#define RILL_LEX_CHAR_PUNCTUATION_SPACE          0x2008
#define RILL_LEX_CHAR_THIN_SPACE                 0x2009
#define RILL_LEX_CHAR_HAIR_SPACE                 0x200A
#define RILL_LEX_CHAR_ZERO_WIDTH_SPACE           0x200B
#define RILL_LEX_CHAR_ZERO_WIDTH_NON_JOINER      0x200C
#define RILL_LEX_CHAR_ZERO_WIDTH_JOINER          0x200D
#define RILL_LEX_CHAR_LINE_SEPARATOR             0x2028
#define RILL_LEX_CHAR_PARAGRAPH_SEPARATOR        0x2029
#define RILL_LEX_CHAR_NARROW_NONBREAKING_SPACE   0x202F
#define RILL_LEX_CHAR_MEDIUM_MATHEMATICAL_SPACE  0x205F
#define RILL_LEX_CHAR_WORD_JOINER                0x2060
#define RILL_LEX_CHAR_IDEOGRAPHIC_SPACE          0x3000
#define RILL_LEX_CHAR_BOM                        0xFEFF

/* non-whitespace characters */
#define RILL_LEX_CHAR_ZERO               '0'
#define RILL_LEX_CHAR_ONE                '1'
#define RILL_LEX_CHAR_TWO                '2'
#define RILL_LEX_CHAR_THREE              '3'
#define RILL_LEX_CHAR_FOUR               '4'
#define RILL_LEX_CHAR_FIVE               '5'
#define RILL_LEX_CHAR_SIX                '6'
#define RILL_LEX_CHAR_SEVEN              '7'
#define RILL_LEX_CHAR_EIGHT              '8'
#define RILL_LEX_CHAR_NINE               '9'
#define RILL_LEX_CHAR_LEFT_SQUARE_BRACE  '['
#define RILL_LEX_CHAR_RIGHT_SQUARE_BRACE ']'
#define RILL_LEX_CHAR_LEFT_CURLY_BRACE   '{'
#define RILL_LEX_CHAR_RIGHT_CURLY_BRACE  '}'
#define RILL_LEX_CHAR_LEFT_ROUND_BRACE   '('
#define RILL_LEX_CHAR_RIGHT_ROUND_BRACE  ')'
#define RILL_LEX_CHAR_COLON              ':'
#define RILL_LEX_CHAR_SEMICOLON          ';'
#define RILL_LEX_CHAR_DOT                '.'
#define RILL_LEX_CHAR_DASH               '-'
#define RILL_LEX_CHAR_E_LOWER            'e'
#define RILL_LEX_CHAR_E_UPPER            'E'
#define RILL_LEX_CHAR_X_LOWER            'x'
#define RILL_LEX_CHAR_X_UPPER            'X'
#define RILL_LEX_CHAR_BACKSLASH          '\\'
#define RILL_LEX_CHAR_QUOTEMARK_SINGLE   '\''
#define RILL_LEX_CHAR_QUOTEMARK_DOUBLE   '"'

/* language syntax */
#define RILL_LEX_CHAR_ENUM_BEGIN             RILL_LEX_CHAR_LEFT_CURLY_BRACE
#define RILL_LEX_CHAR_ENUM_END               RILL_LEX_CHAR_RIGHT_CURLY_BRACE
#define RILL_LEX_CHAR_QUOTE_BEGIN            RILL_LEX_CHAR_LEFT_SQUARE_BRACE
#define RILL_LEX_CHAR_QUOTE_END              RILL_LEX_CHAR_RIGHT_SQUARE_BRACE
#define RILL_LEX_CHAR_COMMENT_BEGIN          RILL_LEX_CHAR_LEFT_ROUND_BRACE
#define RILL_LEX_CHAR_COMMENT_END            RILL_LEX_CHAR_RIGHT_ROUND_BRACE
#define RILL_LEX_CHAR_COMPILE_MODE_BEGIN     RILL_LEX_CHAR_COLON
#define RILL_LEX_CHAR_COMPILE_MODE_END       RILL_LEX_CHAR_SEMICOLON
#define RILL_LEX_CHAR_NUMERIC_DECIMAL        RILL_LEX_CHAR_DOT
#define RILL_LEX_CHAR_NUMERIC_NEGATOR        RILL_LEX_CHAR_DASH
#define RILL_LEX_CHAR_EXPONENT_MARK_LOWER    RILL_LEX_CHAR_E_LOWER
#define RILL_LEX_CHAR_EXPONENT_MARK_UPPER    RILL_LEX_CHAR_E_UPPER
#define RILL_LEX_CHAR_HEX_ESCAPE_LOWER       RILL_LEX_CHAR_X_LOWER
#define RILL_LEX_CHAR_HEX_ESCAPE_UPPER       RILL_LEX_CHAR_X_UPPER
#define RILL_LEX_CHAR_STRING_ESCAPE          RILL_LEX_CHAR_BACKSLASH
#define RILL_LEX_CHAR_STRING_DELIM_SINGLE    RILL_LEX_CHAR_QUOTEMARK_SINGLE
#define RILL_LEX_CHAR_STRING_DELIM_DOUBLE    RILL_LEX_CHAR_QUOTEMARK_DOUBLE

int rlexchr_ws ( int c );
int rlexchr_strdelim ( int c );

int rlexchr_idopen ( int c );
int rlexchr_idbody ( int c );

int rlexchr_numopen ( int c );
int rlexchr_numbody ( int c );

#endif

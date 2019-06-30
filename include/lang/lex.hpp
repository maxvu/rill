#ifndef RILL_LEX
#define RILL_LEX

namespace rill {
namespace lang {

    enum lex_token_type {
        WHITESPACE,
        COMMENT,
        NUMERIC,
        STRING,
        COMPILE_MODE_OPEN,
        COMPILE_MODE_CLOSE,
        QUOTATION_OPEN,
        QUOTATION_CLOSE,
        STRUCTURE_OPEN,
        STRUCTURE_CLOSE,
        IMPORT_OPEN,
        IMPORT_CLOSE
    };

    class lex_token {

        protected:
        lex_token_type _type;
        string         _text;
        string         _unit_name;
        unsigned int   _line;
        unsigned int   _offset;

        public:
        lex_token ( lex_token_type type, const string & text );
        lex_token_type type () const;
        const string & text () const;
        unsigned int line () const;
        unsigned int offset () const;

    };

    class lexer {

        protected:
        unsigned int _line;
        unsigned int _offset;

        lexer ( const unit & unit );
        vector<lex_token> operator()() ();

    };

}
}

#endif

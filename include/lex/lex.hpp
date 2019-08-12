#ifndef RILL_LEX
#define RILL_LEX

namespace rill {

    class lex_token {
        public:
        enum type {
            WHITESPACE,
            COMMENT,
            WORD,
            NUMERIC,
            STRING,
            QUOTE_OPEN,
            QUOTE_CLOSE,
            STRUCT_OPEN,
            STRUCT_CLOSE
        };

        protected:
        type   _type;
        string _text;

        type type () const;
        const string & text () const;
    };

    vector<lex_token> lex ( const string & src );

}

#endif

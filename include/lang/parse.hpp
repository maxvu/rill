#ifndef RILL_PARSE
#define RILL_PARSE

namespace rill {
namespace lang {

    enum ast_node_type {
        COMMENT,
        INVOCATION,
        DEFINITION,
        LITERAL_INT,
        LITERAL_UINT,
        LITERAL_FLOAT,
        LITERAL_STR,
        STRUCTURE,
        QUOTATION,
        IMPORT
    };

    class ast_node : public refcounted {

        protected:
        ref<ast_node> _parent;

        public:
        virtual ast_node_type type () =0;
        ast_node * up () const;

    };

    class ast_node_comment : public ast_node {

        protected:
        lex_token _token;

        public:
        ast_node_comment ( const lex_token & comment_token );
        ast_node_type type () const;
        const string & body ();

    };

    class ast_node_invocation {

        protected:
        lex_token _called_word;

        public:
        ast_node_invocation ( const lex_token & call_token );
        ast_node_type type () const;
        const string & called_word () const;

    };

    class ast_node_definition {

        protected:
        lex_token             _name_token;
        lex_token             _open_token;
        lex_token             _close_token;
        vector<ref<ast_node>> _definition;

        const vector<ast_node> & definition (
            const string & name,
            const lex_token & open,
            const vector<ref<ast_node>> & definition,
            const lex_token & close,
        ) const;
        ast_node_type type () const;

    };

    class ast_node_literal_str : public ast_node {
        protected:
        lex_token _token;

        public:
        ast_node_literal_str ( const lex_token & token );
        ast_node_type type () const;
        const string & body () const;
        const lex_token & token () const;
    };

    class ast_node_literal_int : public ast_node {
        protected:
        lex_token _token;

        public:
        ast_node_literal_int ( const lex_token & token );
        ast_node_type type () const;
        int value () const;
        const lex_token & token () const;
    };

    class ast_node_literal_uint : public ast_node {
        protected:
        lex_token _token;

        public:
        ast_node_literal_uint ( const lex_token & token );
        ast_node_type type () const;
        unsigned int value () const;
        const lex_token & token () const;
    };

    class ast_node_literal_double : public ast_node {
        protected:
        lex_token _token;

        public:
        ast_node_literal_uint ( const lex_token & token );
        ast_node_type type () const;
        double value () const;
        const lex_token & token () const;
    };

    class ast_node_structure {

        protected:
        lex_token             _open_token;
        lex_token             _close_token;
        vector<ref<ast_node>> _body;

        public:
        ast_node_structure (
            const lex_token & open,
            const vector<ref<ast_node>> & body,
            const lex_token & close
        );
        ast_node_type type () const;

    };

    class ast_node_quotation {

        protected:
        string                _name;
        lex_token             _open_token;
        vector<ref<ast_node>> _body;
        lex_token             _close_token;

        public:
        ast_node_quotation(
            const string & name,
            const lex_token & open,
            const vector<ref<ast_node>> & body,
            const lex_token & close,
        );
        ast_node_type type () const;

    };

    class ast_tree {

        protected:
        ref<ast_node> _root;

        public:
        ast_tree ();

    };

    ast_tree parse ( const vector<lex_token> & tokens );

}
}

#endif

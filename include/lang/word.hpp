#ifndef RILL_LANG_WORD
#define RILL_LANG_WORD

namespace rill {
namespace lang {

    class word {

        protected:
        site         _site;
        vector<word> _nested_definitions;

        public:
        const site & site () const;

    };

    class invocation : public word {

        protected:
        string _name;

        public:
        reference_word ();
        const string & name () const;

    };

    class recursive_word : public word {

        protected:
        vector<word> _elements;

        public:
        structure ( const site & site, const vector<word> & elements );

    };

    class structure : public recursive_word {

    };

    class quotation : public recursive_word {

    };

}
}

#endif

#ifndef RILL_BUILDER
#define RILL_BUILDER

namespace rill {
namespace builder {

    class builder {

        protected:
        vector<rval>                   _constants;
        hashmap<string, block>         _built_blocks;
        hashmap<string, ref<ast_node>> _unresolved_blocks;
        string                         _code;

        public:
        builder ();

        builder & add_word ( const word & word );
        program build () const;

    };

}
}

#endif

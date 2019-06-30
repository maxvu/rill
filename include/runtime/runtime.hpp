#ifndef RILL_RUNTIME
#define RILL_RUNTIME

namespace rill {

    class runtime {

        protected:
        word                 _entry;
        vector<extension>    _extensions;
        hashmap<string,unit> _units;
        vector<rval>         _constants;

        public:
        runtime ();

        runtime & load_unit ( const compilation_unit & unit );

        vm build_vm () const;

    };

}

#endif

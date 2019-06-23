#ifndef RILL_VM
#define RILL_VM

namespace rill {

    class vm {

        friend vm_builder;

        protected:
        unsigned int           _counter;
        program                _program;
        vector<rval>           _data_stack;
        vector<rval>           _side_stack;
        vector<unsigned int>   _call_stack;
        vector<extension_type> _extension_types;
        vector<extension_word> _extension_words;
        flags                  _flags;

        vm ();
        vm ( const vm & that ) =0;
        vm ( vm && that ) =0;
        vm & operator= ( const vm & that ) =0;
        vm & operator= ( const vm && that ) =0;

        public:
        ~vm ();

        vm & step ();
        vm & run ();
        vm & reset ();

    };

    class vm_ext_view {

        protected:
        vm & vm;

        public:
        vm_extension_view ( vm & vm );

        vm_extension_view & push ( const rval & val );
        rval pop ();

    };

    class vm_builder {

        protected:
        vector<extension_type>     _extension_types;
        map<string,extension_word> _extension_words;

        public:
        vm_builder ();

        vm_builder & register_type ( const extension_type & type );
        vm_builder & register_word ( const extension_word & type );

        vm build ( program program ) const;

    };


}

#endif

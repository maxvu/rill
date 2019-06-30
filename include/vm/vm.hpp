#ifndef RILL_VM
#define RILL_VM

namespace rill {

    class vm_ext_view;
    typedef (*extension_word)(vm_ext_view&);

    class vm {

        protected:
        unsigned int           _counter;
        string                 _code;
        vector<rval>           _constants;
        vector<rval>           _data_stack;
        vector<rval>           _side_stack;
        vector<unsigned int>   _call_stack;
        vector<extension_word> _extension_words;
        flags                  _flags;

        public:
        vm (
            const string & code,
            const vector<rval> & constants,
            const vector<extension_word> & extension_words
        );
        vm ( const vm & that ) =0;
        vm ( vm && that ) =0;
        vm & operator= ( const vm & that ) =0;
        vm & operator= ( const vm && that ) =0;
        ~vm ();

        unsigned int counter () const;
        const string & code () const;
        const vector<rval> & constants () const;
        const vector<rval> & data_stack ();
        const vector<rval> & side_stack ();
        const vector<rval> & call_stack ();
        const vector<extension_word> & extension_words ();
        flags & flags ();
        const flags & flags () const;

        vm & step ();
        vm & run ();
        vm & reset ();

    };

}

#endif

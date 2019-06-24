#ifndef RILL_LANG_PROGRAM
#define RILL_LANG_PROGRAM

namespace rill {
namespace lang {

    class program {

        protected:
        map<string,word>      _words;
        map<string,type>      _types;
        map<string,typeclass> _typeclasses;

        public:
        program ();

    };

}
}

#endif

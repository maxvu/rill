#ifndef RILL_VM_PROGRAM
#define RILL_VM_PROGRAM

namespace rill {
namespace vm {

    class program {

        protected:
        string             _code;
        vector<rval>       _constants;
        map<string,string> _dependencies; // TODO: dedicated type

        public:

        program (
            const string & code,
            const vector<rval> & constants
        );

        const string & code () const;
        const vector<rval> & constants () const;
        const map<string,string> & dependencies () const;

    };

}
}

#endif

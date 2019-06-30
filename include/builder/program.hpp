#ifndef RILL_PROGRAM
#define RILL_PROGRAM

namespace rill {
namespace builder {

    class program {

        protected:
        vector<rval> _constants;
        string       _code;
        debug_info * _debug_info;

        public:
        program ();

        const vector<rval> & constants () const;
        const string & code () const;
        const debug_info * debug_info () const;

    };

}
}

#endif

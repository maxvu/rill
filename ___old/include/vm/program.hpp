#ifndef RILL_VM_PROGRAM
#define RILL_VM_PROGRAM

#include "debug_info/debug_info.hpp"
#include "vector.hpp"
#include "vm/rval.hpp"

namespace rill {
namespace vm {

    class program {

        protected:

        vector<unsigned char> _it; // instruction table
        vector<rval>          _ct; // constant table
        debug_info *          _di; // debug info

        public:

        program (
            const vector<unsigned char> & it,
            const vector<rval> & ct
        );

        const vector<unsigned char> instructions () const;
        const vector<rval> constants () const;

    };

}
}

#endif

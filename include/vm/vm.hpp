#ifndef RILL_VM
#define RILL_VM

#include "rval.hpp"
#include "extension.hpp"
#include "vector.hpp"

namespace rill {

    class vm {

        public:
        enum flag {
            PAUSE = 0b001
        };

        protected:
        long          _ip; // instruction pointer
        vector<rval>  _ct; // constant table
        vector<rval>  _ds; // primary data stack
        vector<rval>  _ss; // secondary data stack
        vector<long>  _cs; // call stack
        unsigned int  _fs; // flags
        extension_set _es; // extension set

        public:
        vm ( const program & program );
        vm ( const vm & other );

        vm & run ();
        vm & step ();

        long & ip ();
        vector<rval> & ct ();
        vector<rval> & ds ();
        vector<rval> & ss ();
        vector<long> & cs ();
        extension_set & es ();

        flag get_flag ( flag flag );
        vm & set_flag ( flag flag );
        vm & unset_flag ( flag flag );
    };

}

#endif

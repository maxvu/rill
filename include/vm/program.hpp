#ifndef RILL_PROGRAM
#define RILL_PROGRAM

#include "rval.hpp"
#include "vector.hpp"

#include <cstdint>

namespace rill {

    struct program_info {
        string _name;
        string _author;
        string _license;
        string _version;
    };

    class program {
        program_info *   _info;
        vector<rval>     _constants;    // constant table
        vector<uint8_t>  _ops;          // operation table
        set<string>      _dependencies; // vocab dependencies
    };

    // TODO: program / write to binary
    // TODO: program / load from binary

}

#endif

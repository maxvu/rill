#ifndef RILL_VAL_TYPE
#define RILL_VAL_TYPE

#include <cstddef>

namespace Rill {

    enum RValType {
        NIL = 0,
        IXX = 1,
        UXX = 2,
        FXX = 3,
        BUF = 4,
        VEC = 5,
        MAP = 6,
        HDL = 7
    };

}

#endif

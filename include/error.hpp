#ifndef RILL_ERROR
#define RILL_ERROR

#include <exception>

namespace rill {

    class arg_error : public std::exception {
        const char * what () {
            return "bad argument";
        }
    };

}

#endif

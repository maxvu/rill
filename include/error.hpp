#ifndef RILL_ERROR
#define RILL_ERROR

#include <exception>

namespace rill {

    class internal_error : public std::exception {
        virtual const char * what () const noexcept override {
            return "internal error";
        }
    };

}

#endif

#include "exception.hpp"

namespace rill {

const char * ArgException::what () const noexcept {
    return "invalid argument";
}

}

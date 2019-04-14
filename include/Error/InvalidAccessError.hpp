#ifndef RILL_INVALIDACCESSERROR
#define RILL_INVALIDACCESSERROR

#include "Error/Error.hpp"

namespace Rill {

    class InvalidAccessError : public Error {

        public:

        InvalidAccessError();

        const char * message () const;

    };
}

#endif

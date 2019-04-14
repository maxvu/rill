#ifndef RILL_NULLARGUMENTERROR
#define RILL_NULLARGUMENTERROR

#include "Error/Error.hpp"

namespace Rill {

    class NullArgumentError : public Error {

        public:

        NullArgumentError();

        const char * message () const;

    };

}

#endif

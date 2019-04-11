#ifndef RILL_ERROR_NULLARGUMENTERROR
#define RILL_ERROR_NULLARGUMENTERROR

#include "Error/Error.hpp"

namespace Rill {
namespace Error {

    class NullArgumentError : public Error {

        public:

        NullArgumentError();

        const char * message () const;

    };

}
}

#endif

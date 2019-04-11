#ifndef RILL_ERROR_INVALIDACCESSERROR
#define RILL_ERROR_INVALIDACCESSERROR

#include "Error/Error.hpp"

namespace Rill {
namespace Error {

    class InvalidAccessError : public Error {

        public:

        InvalidAccessError();

        const char * message () const;

    };

}
}

#endif

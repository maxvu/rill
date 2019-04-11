#ifndef RILL_VAL_TYPEMISMATCHERROR
#define RILL_VAL_TYPEMISMATCHERROR

#include "Error/Error.hpp"

using Rill::Error::Error;

namespace Rill {
namespace Val {

    class TypeMismatchError : public Error {

        public:

        TypeMismatchError ( Type expected, Type actual );

        const char * message () const;

    };

}
}

#endif

#ifndef RILL_VAL_TYPEMISMATCHERROR
#define RILL_VAL_TYPEMISMATCHERROR

#include "Error/Error.hpp"

namespace Rill {
namespace Error {

    class TypeMismatchError : public Error {

        public:

        TypeMismatchError ( Type expected, Type actual );

        const char * message () const;

    };

}
}

#endif

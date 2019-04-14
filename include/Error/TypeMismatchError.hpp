#ifndef RILL_TYPEMISMATCHERROR
#define RILL_TYPEMISMATCHERROR

#include "Error/Error.hpp"
#include "Val/ValType.hpp"

namespace Rill {

    class TypeMismatchError : public Error {

        public:

        TypeMismatchError ( ValType expected, ValType actual );

        const char * message () const;

    };

}

#endif

#ifndef RILL_ERRORS_OOMERROR
#define RILL_ERRORS_OOMERROR

#include "Structures/Buffer.hpp"

namespace Rill {
namespace Errors {

    class OOMError {

        Buffer message () const;

    };

}
}

#ifndef RILL_ERRORS_BADARGERROR
#define RILL_ERRORS_BADARGERROR

#include "Structures/Buffer.hpp"

namespace Rill {
namespace Errors {

    class BadArgError {

        Buffer message () const;

    };

}
}

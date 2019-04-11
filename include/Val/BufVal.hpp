#ifndef RILL_VAL_BUFVAL
#define RILL_VAL_BUFVAL

#include "Structures/Buffer.hpp"
#include "Val/Val.hpp"

using Rill::Structures::Buffer;
using Rill::Val::Val;

namespace Rill {
namespace Val {

    class BufVal : public Val, public Buffer {



    };

}
}

#endif

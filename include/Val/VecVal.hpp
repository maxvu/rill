#ifndef RILL_VAL_VECVAL
#define RILL_VAL_VECVAL

#include "Structures/Vector.hpp"
#include "Val/Val.hpp"
#include "Val/VRef.hpp"

using Rill::Structures::Vector;
using Rill::Val::Val;
using Rill::Val::VRef;

namespace Rill {
namespace Val {

    class VecVal : public Val, public Vector<VRef> {



    };

}
}

#endif

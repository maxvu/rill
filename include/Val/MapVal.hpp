#ifndef RILL_VAL_MAPVAL
#define RILL_VAL_MAPVAL

#include "Structures/Map.hpp"
#include "Val/Val.hpp"
#include "Val/VRef.hpp"

using Rill::Structures::Map;
using Rill::Val::Val;
using Rill::Val::VRef;

namespace Rill {
namespace Val {

    class MapVal : public Val, public Map<VRef> {



    };

}
}

#endif

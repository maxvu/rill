#ifndef RILL_MAPVAL
#define RILL_MAPVAL

#include "Structures/Map.hpp"
#include "Val/Val.hpp"
#include "Val/VRef.hpp"

namespace Rill {

    class MapVal : public Val, public Map<VRef> {



    };

}

#endif

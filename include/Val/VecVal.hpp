#ifndef RILL_VECVAL
#define RILL_VECVAL

#include "Structures/Vector.hpp"
#include "Val/Val.hpp"
#include "Val/VRef.hpp"

namespace Rill {

    class VecVal : public Val, public Vector<VRef> {



    };

}

#endif

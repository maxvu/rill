#ifndef RILL_VAL_REF
#define RILL_VAL_REF

#include "Structures/Ref.hpp"
#include "Val/Val.hpp"

using Rill::Structures::Ref;

namespace Rill {
namespace Val {

    class IxxVal;
    class UxxVal;
    class FxxVal;
    class BufVal;
    class VecVal;
    class MapVal;

    class VRef : public Ref<Val> {

        public:

        IxxVal & asIxx ();
        UxxVal & asUxx ();
        FxxVal & asFxx ();
        BufVal & asBuf ();
        VecVal & asVec ();
        MapVal & asMap ();

        const IxxVal & asIxx () const;
        const UxxVal & asUxx () const;
        const FxxVal & asFxx () const;
        const BufVal & asBuf () const;
        const VecVal & asVec () const;
        const MapVal & asMap () const;

    };

}
}

#endif

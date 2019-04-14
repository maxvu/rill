#ifndef RILL_VREF
#define RILL_VREF

#include "Structures/Ref.hpp"
#include "Val/Val.hpp"

namespace Rill {

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

#endif

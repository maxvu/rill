#ifndef RILL_VAL_UXX
#define RILL_VAL_UXX

#include "Config.hpp"
#include "Val/Val.hpp"

namespace Rill {

    class Uxx : public Val {

        protected:

        RILL_UXX_TYPE u;

        public:

        Uxx ();
        Uxx ( RILL_UXX_TYPE u );
        Uxx ( const Uxx & other );

        operator RILL_UXX_TYPE & ();
        operator RILL_UXX_TYPE & () const;

    };

}

#endif

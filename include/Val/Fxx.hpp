#ifndef RILL_VAL_FXX
#define RILL_VAL_FXX

#include "Config.hpp"
#include "Val/Val.hpp"

namespace Rill {

    class Fxx : public Val {

        protected:

        RILL_FXX_TYPE i;

        public:

        Fxx ();
        Fxx ( RILL_FXX_TYPE f );
        Fxx ( const Fxx & other );

        operator RILL_FXX_TYPE & ();
        operator RILL_FXX_TYPE & () const;

        bool isFinite () const;

    };

}

#endif

#ifndef RILL_VAL_REF
#define RILL_VAL_REF

#include "Config.hpp"
#include "Val/Val.hpp"

namespace Rill {

    class Ref {

        protected:

        Val * val;

        public:

        Ref ();
        Ref ( Val * val );
        Ref ( const Ref & other );

    };

}

#endif

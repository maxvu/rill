#ifndef RILL_VAL_FXXVAL
#define RILL_VAL_FXXVAL

#include "Val/Val.hpp"

using Rill::Val::Val;

namespace Rill {
namespace Val {

    class FxxVal : public Val {

        protected:

        double f;

        public:

        FxxVal ();

    };

}
}

#endif

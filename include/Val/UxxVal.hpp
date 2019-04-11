#ifndef RILL_VAL_UXXVAL
#define RILL_VAL_UXXVAL

#include "Val/Val.hpp"

using Rill::Val::Val;

namespace Rill {
namespace Val {

    class UxxVal : public Val {

        protected:

        unsigned int u;

        public:

        UxxVal ();

    };

}
}

#endif

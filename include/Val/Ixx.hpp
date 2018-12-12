#ifndef RILL_VAL_IXX
#define RILL_VAL_IXX

#include "Config.hpp"
#include "Val/Val.hpp"

#include <cstdint>

namespace Rill {

    class Ixx : public Val {

        protected:

        RILL_IXX_TYPE i;

        public:

        Ixx ();
        Ixx ( RILL_IXX_TYPE i );
        Ixx ( const Ixx & other );
        ~Ixx ();

        Val & lease ();
        int release ();
        Val & exclude ();
        Val * clone () const;
        operator bool () const;
        bool operator==  ( const Val & other );
        bool containsRef ( const Val * needle );

        operator RILL_IXX_TYPE & ();
        operator RILL_IXX_TYPE & () const;

    };

}

#endif

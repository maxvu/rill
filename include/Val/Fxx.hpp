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
        ~Fxx ();

        Val & lease ();
        int release ();
        Val & exclude ();
        Val * clone () const;
        operator bool () const;
        bool operator==  ( const Val & other );
        bool contains ( const Val * needle );

        operator RILL_FXX_TYPE & ();
        operator RILL_FXX_TYPE & () const;

        bool isFinite () const;

    };

}

#endif

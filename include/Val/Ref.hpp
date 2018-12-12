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

        Val & operator* ();
        const Val & operator* () const;

        Val * operator-> ();
        const Val * operator-> () const;

        Ref & operator= ( Val * other );
        Ref & operator= ( const Ref & other );

        bool operator== ( Val * other );
        bool operator== ( const Ref & other );

        bool operator!= ( Val * other );
        bool operator!= ( const Ref & other );

        bool contains ( const Ref & needle ) const;

    };

}

#endif

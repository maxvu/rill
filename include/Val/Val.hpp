#ifndef RILL_VAL
#define RILL_VAL

#include "Structures/Refcounted.hpp"
#include "Val/ValType.hpp"

namespace Rill {

    class Val : public Refcounted<Val> {

        virtual ValType type () const =0;
        virtual Val * clone () =0;
        virtual Val * exclude () const =0;
        virtual bool cyclesTo ( const Val * that ) const =0;
        virtual Val * compact () const =0;

    };

}

#endif

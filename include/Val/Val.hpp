#ifndef RILL_VAL_VAL
#define RILL_VAL_VAL

#include "Structures/Refcounted.hpp"

using Rill::Structures::Refcounted;

namespace Rill {
namespace Val {

    class Val : public Refcounted<Val> {

        virtual Type type () const =0;
        virtual Val * clone () =0;
        virtual Val * exclude () const =0;
        virtual bool cyclesTo ( const Val * that ) const =0;
        virtual Val * compact () const =0;

    };

}
}

#endif

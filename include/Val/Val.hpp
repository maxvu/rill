#ifndef RILL_VAL_VAL
#define RILL_VAL_VAL

#include "Val/ValType.hpp"

namespace Rill {

    class Val {

        protected:

        public:

        virtual ~Val ();

        virtual ValType type () =0;
        virtual operator bool () =0;
        virtual Val * clone () =0;
        virtual bool operator== ( const Val & that ) =0;
        bool operator!= ( const Val & that );
        virtual void lease () =0;
        virtual bool release () =0;
        virtual bool containsVal ( const Val * val ) const =0;

    };

}

#endif

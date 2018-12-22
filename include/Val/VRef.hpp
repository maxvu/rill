#ifndef RILL_VAL_VREF
#define RILL_VAL_VREF

namespace Rill {

    class VRef {

        protected:

        Val * val;

        public:

        VRef ();
        VRef ( const VRef & other );
        VRef ( Val * val );
        ~VRef ();

        Val * operator-> ();
        const Val * operator-> () const;

        Val & operator* ();
        const Val & operator* () const;

    };

}

#endif

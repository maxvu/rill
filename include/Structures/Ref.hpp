#ifndef RILL_REF
#define RILL_REF

namespace Rill {

    template <typename T> class Ref {

        protected:

        T * data;

        public:

        Ref ();
        Ref ( T * init_data );
        Ref ( const Ref & that );
        ~Ref ();

        bool isUnique () const;
        Ref & makeUnique ();

        Ref & operator= ( T * new_data );
        Ref & operator= ( const Ref & that );

        T & operator* ();
        T * operator-> ();

        const T & operator* () const;
        const T * operator-> () const;

        const Ref & asConst () const;

    };

}

#endif

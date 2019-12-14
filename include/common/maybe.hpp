#ifndef RILL_MAYBE
#define RILL_MAYBE

namespace rill {

    template <typename T> class maybe {

        protected:

        T *  _entity;

        public:

        maybe ();
        maybe ( const T & entity );

        operator bool () const;
        bool is () const;
        operator const T & () const;
        operator T & ();
        const T & get () const;
        T & get ();

    };

}

#endif

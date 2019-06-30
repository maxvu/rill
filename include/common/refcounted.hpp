#ifndef RILL_REFCOUNTED
#define RILL_REFCOUNTED

namespace rill {

    template <typename T> class refcounted {

        protected:
        unsigned int _refcount;

        public:
        refcounted ();

        T & lease ();
        T & release ();

    };

    template <typename T> class ref {

        protected:
        refcounted<T> * _object;

        public:
        ref ();
        ref ( const refcounted<T> * object );
        ~ref ();

        ref & operator= ( refcounted<T> * object );
        ref & operator= ( const ref<T> & ref );
        T & operator* ();
        const T & operator* () const;

    };

}

#endif

#ifndef RILL_REFCOUNTED
#define RILL_REFCOUNTED

namespace rill {

    template <typename T> class refcounted {

        protected:

        unsigned long _count;

        public:

        const unsigned long & refcount () const;
        T & ref ();
        void deref ();

    };

}

#endif

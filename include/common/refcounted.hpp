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

}

#endif

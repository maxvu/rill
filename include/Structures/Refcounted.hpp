#ifndef RILL_REFCOUNTED
#define RILL_REFCOUNTED

namespace Rill {

    template <typename T> class Refcounted {

        protected:

        size_t count;

        public:

        Refcounted ();

        T * lease ();
        bool release ();

    };

}

#endif

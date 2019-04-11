#ifndef RILL_STRUCTURES_REFCOUNTED
#define RILL_STRUCTURES_REFCOUNTED

namespace Rill {
namespace Structures {

    template <typename T> class Refcounted {

        protected:

        size_t count;

        public:

        Refcounted ();

        T * lease ();
        char release ();

    };

}
}

#endif

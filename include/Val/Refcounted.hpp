#ifndef RILL_VAL_REFCOUNTED
#define RILL_VAL_REFCOUNTED

namespace Rill {
namespace Val {

    struct Refcounted {

        size_t _refcount;

        Refcounted ();
        
    };

}
}

#endif

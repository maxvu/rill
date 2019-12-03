#ifndef RILL_VM_EXTENSION_TYPE
#define RILL_VM_EXTENSION_TYPE

namespace rill {
namespace vm {

    template <typename T> class extension_type : public refcounted<T> {

        virtual const string & type () =0;
        virtual T * clone () =0;
        virtual ~extension_type () =0;

    };

}
}

#endif

#ifndef RILL_VM_EXTENSION_TYPE
#define RILL_VM_EXTENSION_TYPE

namespace rill {
namespace vm {

    class extension_type {

        virtual const string & type () =0;
        virtual extension_type * clone () =0;
        virtual const string to_string () const =0;
        virtual ~extension_type () =0;

    };

}
}

#endif

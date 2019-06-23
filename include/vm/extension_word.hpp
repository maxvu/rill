#ifndef RILL_EXTENSION_WORD
#define RILL_EXTENSION_WORD

namespace rill {
namespace vm {

    class extension_word {

        protected:

        void (*invoke)(vm&);

        public:

        extension_word ( void (*invoke)(vm_ext_view&) );

        void invoke ( vm & vm );

    };

}
}

#endif

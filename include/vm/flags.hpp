#ifndef RILL_FLAGS
#define RILL_FLAGS

namespace rill {
namespace vm {

    class flags {

        protected:
        unsigned long _f;

        public:
        flags ();

        bool halt () const;
        flags & halt ( bool on ) const;

    };

}
}

#endif

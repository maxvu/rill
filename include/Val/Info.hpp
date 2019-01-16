#ifndef RILL_VAL_INFO
#define RILL_VAL_INFO

#include "Config.hpp"

namespace Rill {
namespace Val {

    enum class Type {
        NIL,
        IXX,
        UXX,
        FXX,
        BUF,
        VEC,
        MAP
    };

    typedef uint8_t Tag;

    class Info {

        protected:

        RILL_UXX_TYPE i_;

        public:

        Info ( Type type );
        Info ( Type type, Tag, );
        Info ( const Info & other );

        Type type () const;
        Info & setType ( Type type );

        Tag tag () const;
        Info & setTag ( Tag tag );

    };

}
}

#endif

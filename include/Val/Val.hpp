#ifndef RILL_VAL_VAL
#define RILL_VAL_VAL

#include "Config.hpp"

namespace Rill {
namespace Val {

    typedef class Map Map;
    typedef class Vector Vector;

    class Val {

        protected:

        Info info_;
        union {
            RILL_IXX_TYPE ixx_;
            RILL_UXX_TYPE uxx_;
            RILL_FXX_TYPE fxx_;
            Buffer *      buf_;
            Vector *      vec_;
            Map *         map_;
        };

        public:

        static Val fromIxx ( RILL_IXX_TYPE i );
        static Val fromUxx ( RILL_UXX_TYPE u );
        static Val fromIxx ( RILL_FXX_TYPE f );
        static Val fromBuf ( Buffer * buf );
        static Val fromVec ( Vector * vec );
        static Val fromMap ( Map * map );

        Val ();
        Val ( const Val & other );
        ~Val ();

        Type type () const;
        bool isNil () const;

        Val & operator= ( const Val & other );
        Val & operator== ( const Val & other );

        Val & exclude ();
        bool cyclesTo ( const Val & other ) const;

        Val clone () const;
        operator bool () const;

        RILL_IXX_TYPE & asIxx ();
        RILL_UXX_TYPE & asUxx ();
        RILL_FXX_TYPE & asFxx ();
        Buffer & asBuf ();
        Vector & asVec ();
        Map & asMap ();

        const RILL_IXX_TYPE & asIxx () const;
        const RILL_UXX_TYPE & asUxx () const;
        const RILL_FXX_TYPE & asFxx () const;
        const Buffer & asBuf () const;
        const Vector & asVec () const;
        const Map & asMap () const;

        Val toJSON () const;

    };

}
};

#endif

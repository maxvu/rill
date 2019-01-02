#ifndef RILL_VAL_VAL
#define RILL_VAL_VAL

#include "Config.hpp"
#include "Val/Type.hpp"

#include <cstddef>
#include <vector>
#include <unordered_map>

namespace Rill {

    typedef class Buf Buf;
    typedef class Vec Vec;
    typedef class Map Map;

    class Val {

        protected:

        RValType _type;
        union {
            RILL_IXX_TYPE ixx;
            RILL_UXX_TYPE uxx;
            RILL_FXX_TYPE fxx;
            Buf *         buf;
            Vec *         vec;
            Map *         map;
        };

        public:

        Val ();
        Val ( const Val & other );
        ~Val ();

        bool operator== ( const Val & other ) const;
        bool operator!= ( const Val & other ) const;
        Val & operator= ( const Val & other );

        RILL_IXX_TYPE & asIxx ();
        RILL_UXX_TYPE & asUxx ();
        RILL_FXX_TYPE & asFxx ();
        Buf & asBuf ();
        Vec & asVec ();
        Map & asMap ();

        Vec & unlock () const;

        const RILL_IXX_TYPE & asIxx () const;
        const RILL_UXX_TYPE & asUxx () const;
        const RILL_FXX_TYPE & asFxx () const;
        const Buf & asBuf () const;
        const Vec & asVec () const;
        const Map & asMap () const;

        RValType type () const;
        bool isNil () const;
        bool isFixedWidth () const;
        bool isRecursive () const;
        bool isShared () const;
        Val & lease ();
        Val & release ();
        bool canCycleWith ( const Val & other ) const;
        operator bool () const;
        Val clone () const;
        Val & compact ();
        Buf serialize () const;

    };

    class Refcounted {

        friend class Val;

        protected:

        size_t refcount;

        public:

        Refcounted ();

    };

}

#endif

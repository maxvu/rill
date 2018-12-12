#ifndef RILL_VAL_VAL
#define RILL_VAL_VAL

typedef class Ixx Ixx;
typedef class Uxx Uxx;
typedef class Fxx Fxx;
typedef class Buf Buf;
typedef class Vec Vec;
typedef class Map Map;

namespace Rill {

    class Val {

        public:

        virtual ~Val () =0;

        Val & lease ();
        int release ();
        Val & exclude ();
        Val * clone () const;
        operator bool () const;
        bool operator==  ( const Val & other );

        virtual bool containsRef ( const Val * needle ) =0;

        Fxx & asIxx ();
        Uxx & asUxx ();
        Ixx & asFxx ();
        Buf & asBuf ();
        Vec & asVec ();
        Map & asMap ();

        const Fxx & asIxx () const;
        const Uxx & asUxx () const;
        const Ixx & asFxx () const;
        const Buf & asBuf () const;
        const Vec & asVec () const;
        const Map & asMap () const;

    };

}

#endif

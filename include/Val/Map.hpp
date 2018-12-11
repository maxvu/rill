#ifndef RILL_VAL_MAP
#define RILL_VAL_MAP

#include "Val/Ref.hpp"
#include "Val/Val.hpp"

namespace Rill {

    struct MapSlot {
        Ref key;
        Ref val;
    };

    class ConstMapIter {

        protected:

        Ref * position;

        public:

        ConstMapIter ( Ref * position );

        ConstMapIter & operator++ ();
        operator bool () const;

        Buffer & key () const;
        Val & val () const;

    };

    class MapIter : public ConstMapIter {

        public:

        Val & val ();

    };

    class Map : public Val {

        protected:

        Slab<MapSlot> slots;
        size_t len;

        public:

        Map ();
        Map ( const Map & other );

        size_t size () const;
        double load () const;

        Map & reserve ( size_t n_items );
        Map & compact ();

        Ref & operator[] ( const Buffer & key );
        const Ref & operator[] ( const Buffer & key ) const;
        Map & unset ( const Buffer & key );

        Map & clear ();

        MapIter begin ();

    };

}

#endif

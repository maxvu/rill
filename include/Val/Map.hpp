#ifndef RILL_VAL_MAP
#define RILL_VAL_MAP

#include "Val/Ref.hpp"
#include "Val/Val.hpp"

#include <initializer_list>

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

        Buf & key () const;
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
        Map ( size_t initial_capacity );
        Map ( std::initializer_list<Ref> vals );
        Map ( const Map & other );

        Val & lease ();
        int release ();
        Val & exclude ();
        Val * clone () const;
        operator bool () const;
        bool operator==  ( const Val & other );
        bool contains ( const Val * needle );

        size_t size () const;
        double load () const;

        Map & reserve ( size_t n_items );
        Map & compact ();

        bool has ( const Buf & key ) const;
        Ref & get ( const Buf & key );
        const Ref & set ( const Buf & key, Ref & val ) const;
        Map & unset ( const Buf & key );

        Vec keys () const;
        Vec vals () const;

        Map & clear ();

        ConstMapIter begin () const;
        ConstMapIter end () const;
        MapIter begin ();
        MapIter end ();

    };

}

#endif

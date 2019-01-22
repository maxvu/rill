#ifndef RILL_VAL_MAP
#define RILL_VAL_MAP

#include "Val/Refcounted.hpp"
#include "Val/Val.hpp"

#include <cstddef>

#define RILL_RMAP_MINSIZ 4
#define RILL_RMAP_DEFSIZ 12
#define RILL_RMAP_GROWTH 2.0
#define RILL_RMAP_MAXLOD 0.90

namespace Rill {
namespace Val {

    class Map {

        struct Slot {
            Val key_;
            Val val_;

            static void swap ( Slot & a, Slot & b );
            bool isEmpty () const;
        };

        protected:

        Slot * slots_;
        size_t occ_;
        size_t cap_;

        public:

        Map ();
        Map ( size_t init_cap );
        Map ( const Map & that );
        ~Map ();

        size_t size () const;
        double load () const;

        Map & reserve ( size_t cap );
        Map & compact ();

        Map & operator= ( const Map & that );
        bool operator== ( const Map & that ) const;

        Map & set ( const Buffer & key );
        Val get ( const Buffer & key );
        bool has ( const Buffer & key ) const;
        Map & unset ( const Buffer & key ) const;
        Map & merge ( const Map & that );
        Map & clear ();

        operator bool () const;

        Val keys () const;
        Val vals () const;

        class Iter {

            protected:

            Map & map;
            size_t pos;

            public:

            Iter ( Map & map );

            Iter & operator++ (int);
            const Buffer & key () const;
            Val & val ();
            Iter & remove ();
            operator bool () const;

        };

        class ConstIter {

            protected:

            const Map & map;
            size_t pos;

            public:

            ConstIter ( const Map & map );

            ConstIter & operator++ (int);
            const Buffer & key () const;
            const Val & val ();
            operator bool () const;

        };

        Iter begin ();
        ConstIter begin () const;

    };

}
}

#endif

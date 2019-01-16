#ifndef RILL_VAL_MAP
#define RILL_VAL_MAP

#include "Val/Refcounted.hpp"

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
        };

        protected:

        Slot * slots_;
        size_t occ_;
        size_t cap_;

        public:

        Map ();
        Map ( const Map & that );
        ~Map ();

        size_t size () const;

        Map & reserve ( size_t cap );
        Map & compact ();

        Map & operator= ( const Map & that );
        bool operator== ( const Map & that ) const;

        Map & set ( const Buffer & key );
        Val get ( const Buffer & key );
        bool has ( const Buffer & key ) const;
        Map & merge ( const Map & that );
        Map & clear ();

        Val keys () const;
        Val vals () const;

    };

}
}

#endif

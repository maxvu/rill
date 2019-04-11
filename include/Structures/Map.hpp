#ifndef RILL_STRUCTURES_MAP
#define RILL_STRUCTURES_MAP

#include "Structures/Buffer.hpp"

namespace Rill {
namespace Structures {

    template <typename T> class Map {

        struct Slot {

            Buffer key;
            T val;

            Slot ( const Buffer & key, const T & val );

        };

        class Iter {

            protected:

            Map & map;
            size_t pos;

            public:

            Iter ( Map & map );

            Iter & operator++ (int);
            const Buffer & key () const;
            T & val ();
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
            const T & val () const;
            operator bool () const;

        };

        protected:

        Slot * slots;
        size_t len;
        size_t cap;

        public:

        Map ();
        Map ( size_t initial_capacity );
        Map ( const Map & that );
        Map ( const Map && that );
        ~Map ();

        size_t size () const;
        size_t capacity () const;
        double load () const;
        Map & reserve ( size_t new_capacity );
        Map & compact ();

        T & get ( const char * key );
        const T & get ( const char * key ) const;
        T & set ( const char * key, const T & val );
        Map & unset ( const char * key );

        Map & clear ();

        bool operator== ( const Map & that ) const;
        bool operator!= ( const Map & that ) const;
        operator bool () const;

        Map & subsume ( const Map & that );

        Iter & begin ();
        ConstIter & begin () const;

    };

}
}

#endif

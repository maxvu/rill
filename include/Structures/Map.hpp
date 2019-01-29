#ifndef RILL_STUCTURES_MAP
#define RILL_STUCTURES_MAP

#include "Structures/Vector.hpp"

#include <cstddef>

namespace Rill {
namespace Structures {

    template <typename K, typename V> class Map {

        public:

        static size_t hash_a ( const K & key );
        static size_t hash_b ( const K & key );
        static size_t hash_c ( const K & key );
        static size_t hash_d ( const K & key );

        protected:

        struct Slot {
            K _key;
            V _value;
        };

        Slot * _slots;
        size_t _capacity;
        size_t _size;

        Map & _resize ( size_t new_capacity );

        public:

        Map ();
        Map ( size_t initial_capacity );
        Map ( const Map & that );
        Map ( const Map && that );
        ~Map ();

        size_t size () const;
        double load () const;
        Map & reserve ( size_t new_capacity );
        Map & compact ();
        Map & clear ();

        bool has ( const K & key ) const;
        Map & set ( const K & key, const V & val );
        Map & unset ( const K & key, const V & val );

        V & operator[] ( const K & key );
        const V & operator[] ( const K & key ) const;

        Map & operator= ( const Map & that );
        bool operator== ( const Map & that ) const;
        bool operator!= ( const Map & that ) const;

        Vector<K> keys () const;
        Vector<V> vals () const;

        class Iter {

            protected:

            Map<K,V> & _map;
            Slot *     _position;

            public:

            Iter ();
            Iter ( const Iter & that );

            Iter & operator++ (int);
            operator bool () const;
            const K & key () const;
            V & val ();
            Iter & unset ();

        };

        class ConstIter {

            protected:

            Map<K,V> & _map;
            Slot *     _position;

            public:

            ConstIter ();
            ConstIter ( const Iter & that );

            ConstIter & operator++ (int);
            operator bool () const;
            const K & key () const;
            const V & val ();

        };

        Iter begin ();
        ConstIter begin () const;

    };

}
}

#endif

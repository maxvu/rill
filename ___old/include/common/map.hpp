#ifndef RILL_MAP
#define RILL_MAP

#include <initializer_list>

#include "pair.hpp"
#include "string.hpp"
#include "vector.hpp"

namespace rill {

    template <typename K, typename V> class map {

        protected:

        struct slot {
            K _key;
            V _val;
        };

        slab<slot>    _slots;
        unsigned long _size;
        unsigned long _capacity;

        public:

        map ();
        map ( unsigned long init_size );
        map ( const map & other );
        map ( map && other );
        map ( std::initializer_list< pair<K,V> > init_list );

        unsigned long size () const;

        map<K,V> & reserve ( unsigned long new_capacity );
        map<K,V> & compact ();

        V & operator[] ( const K & key );
        const V & operator[] ( const K & key ) const;

        bool has ( const K & key ) const;
        const V & get ( const K & key ) const;
        V & get ( const K & key );
        map<K,V> & remove ( const K & key );

        map<K,V> & operator= ( const map<K,V> & other );
        map<K,V> & operator= ( map<K,V> && other );

        vector<K> keys () const;
        vector<V> vals () const;
        map<K,V> & subsume ( const map<K,V> & other );

        map<K,V> & clear ();

        protected:

        template <typename M> class iter_base {

            protected:

            M map;
            unsigned long index;

            public:

            void operator++ ( int );
            const K & key () const;
            const V & val () const;
            operator bool () const;

        };

        public:

        class iter : public iter_base< map<K,V> & > {

            public:

            iter ( map<K,V> & map );

            V & val ();
            iter & remove ();

        };

        class const_iter : public iter_base< const map<K,V> & > {

            public:

            const_iter ( const map<K,V> & map );

        };

        const_iter begin () const;
        iter begin ();

    };

}

#endif

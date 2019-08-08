#ifndef RILL_HASHMAP
#define RILL_HASHMAP

#include "string.hpp"

namespace rill {

    template <typename K, typename V> class hashmap {

        public:
        static unsigned long MINIMUM_SIZE;
        static unsigned long DEFAULT_SIZE;
        static double        GROWTH_RATE;

        struct slot {
            K key;
            V val;
        };

        protected:

        slot * _slots;
        unsigned long _size;
        unsigned long _capacity;

        public:

        hashmap ();
        hashmap ( const hashmap<K,V> & that );
        hashmap ( hashmap<K,V> && that );
        hashmap ( std::initializer_list<hashmap<K,V>::slot> init_list );
        ~hashmap ();

        bool has ( const K & key ) const;
        V & get ( const K & key );
        V & remove ( const K & key );
        V & operator[] ( const K & key );
        const V & operator[] ( const K & key ) const;

        hashmap<K,V> operator+ ( const hashmap<K,V> & that ) const;
        hashmap<K,V> & operator+= ( const hashmap<K,V> & that );

        protected:
        template <typename H> class iter_base {
            protected:
            H map;

            public:
            iter_base ( H map );

            iter_base & operator++ ( int );
            operator bool () const;
            const K & key () const;
            const V & val () const;
        };

        public:
        class iter : public iter_base<hashmap<K,V> &> {
            V & val ();
        };
        class const_iter : public iter_base<const hashmap<K,V> &> {};

        const_iter begin () const;
        iter begin ();

    };

}

#endif

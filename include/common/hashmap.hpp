#ifndef RILL_HASHMAP
#define RILL_HASHMAP

#include "vector.hpp"

namespace rill {

    template <typename K, typename V> class hashmap {

        protected:

        struct slot {
            slot ( const K & k, const V & v );
            K _key;
            V _val;
        };

        vector<slot>  _slots;
        unsigned long _size;
        unsigned long _capacity;

        public:

        hashmap ();
        hashmap ( const hashmap & that );
        hashmap ( const hashmap && that );
        ~hashmap ();

        unsigned long size () const;
        double load () const;
        hashmap & reserve ( unsigned long new_capacity );
        hashmap & compact ();
        bool has ( const K & key ) const;
        V & get ( const K & key );
        const V & get ( const K & key ) const;
        hashmap & set ( const K & key, const V & val );
        hashmap & unset ( const K & key );
        hashmap & merge ( hashmap & that );
        hashmap & clear ();

        hashmap & operator= ( const hashmap & that );
        hashmap & operator= ( hashmap && that );
        bool operator== ( const hashmap & that ) const;
        bool operator!= ( const hashmap & that ) const;

        protected:
        template <typename M, typename I> class iter_base {

            protected:
            M _map;
            unsigned long i;

            public:
            iter_base ( M map );
            I & operator++ (int);
            operator bool () const;
            const K & key () const;
            const V & operator* () const;
            V & val ();

        };

        public:
        class iter : public iter_base<hashmap&, iter> {

            public:
            V & operator* ();
            iter & remove ();

        };
        iter begin ();

        class const_iter : public iter_base<const hashmap&, const_iter> {};
        const_iter begin () const;

    };

}

#endif

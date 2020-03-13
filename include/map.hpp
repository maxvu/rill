#ifndef RILL_MAP
#define RILL_MAP

#include <initializer_list>
#include "pair.hpp"

namespace rill {

    template <typename K, typename V>
    class map {

        protected:

            array<pair<K,V>> _slots;
            size_t           _occ;

        public:

            map ();
            map ( size_t init_cap );
            map ( std::initializer_list<pair<K,V>> init_list );
            map ( const map<K,V> & that );
            ~map ();

            size_t size () const;
            map<K,V> & reserve ( size_t new_cap );
            map<K,V> & compact ();

            bool has ( const K & key ) const;
            K & get ( const K & get );
            map<K,V> & remove ( const K & key );

            map<K,V> & clear ();

        protected:

            template <typename M, typename I>
            class iter_base {

                protected:
                    M      _map;
                    size_t _pos;

                public:
                    iter_base ( M map );

                    I operator++ ();
                    operator bool () const;
                    const K & key () const;
                    const V & val () const;

            };

        public:

            class const_iter : iter_base<const map<K,V>,const_iter> {

            };

            class iter : iter_base<map<K,V>,iter> {

                public:

                    V & val ();

            };

        iter begin ();
        const_iter begin () const;

    };

}

#endif

#ifndef RILL_MAP
#define RILL_MAP

#include "tuple.hpp"

namespace rill {

    template <typename K, typename V> class Map {

        protected:
            Array<Tuple<K,V>> slots;
            size_t      occ;

        public:
            Map ();
            Map ( size_t init_cap );
            Map ( const Map & that );
            Map ( Map && that );
            Map ( std::initializer_list<Tuple<K,V>> );

            size_t size () const;
            bool is_empty () const;

            bool has ( const K & key ) const;
            V & get ( const K & key );
            const V & get ( const K & key ) const;
            Map<K,V> & del ( const K & key ) const;

            Map<K,V> & clear ();

            template <typename I, typename M> class IterBase {

                protected:
                    M      map;
                    size_t pos;

                public:
                    IterBase ( M map );

                    I operator++ ();
                    operator bool ();
                    const V & operator* () const;
                    const K & key () const;
                    const V & val () const;

            };

            class Iter : IterBase<Iter,Map&> {

                public:
                    V & operator* ();
                    V & val ();

            };

            class ConstIter : IterBase<ConstIter,const Map&> {};

            Iter begin ();
            ConstIter begin () const;

    };

}

#endif

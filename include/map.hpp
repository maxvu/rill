#ifndef RILL_MAP
#define RILL_MAP

namespace rill {

    template <typename K, typename V> class map {

        public:
            constexpr static size_t DEFAULT_SIZE = 16;
            constexpr static float  GROWTH_RATE  = 2.0;

            class slot {
                K _key;
                V _val;
            };

        protected:
            array<slot> _slots;
            size_t      _size;

        public:
            map ();
            map ( const map<K,V> & that );
            map ( map<K,V> && that );
            ~map ();

            map<K,V> & operator= ( const map<K,V> & that );
            map<K,V> & operator= ( map<K,V> && that );

            size_t size () const;
            size_t capacity () const;
            map<K,V> & reserve ( size_t new_capacity );
            map<K,V> & compact ();

            bool has ( const K & key ) const;
            const V & get ( const K & key ) const;
            V & get ( const K & key );
            map<K,V> & set ( const K & key );
            map<K,V> & unset ( const K & key );

            const V & operator[] ( const K & key ) const;
            V & operator[] ( size_t index );

            bool operator== ( const map<K,V> & that ) const;
            bool operator!= ( const map<K,V> & that ) const;

            map<K,V> & operator+= ( const map<K,V> & that );
            map<K,V> & operator+ ( const map<K,V> & that ) const;

            map<K,V> intersect ( const map<K,V> & that ) const;

            vector<K> keys () const;
            vector<V> values () const;

        protected:
            template <typename M> class iter_base {
                protected:
                    M map;

                public:
                    iter_base ( M map );
                    const K & key () const;
                    const V & value () const;
                    const V & operator* () const;
                    iter_base<M> & operator++ ( int );
                    operator bool () const;
            };

        public:
            class iter : iter_base<map<K,V>&> {
                public:
                    iter ( map<K,V> & map );
                    V & value ();
                    V & operator* ();
                    iter & unset ();
            };
            friend class iter;

            iter & begin ();

            class const_iter : iter_base<const map<K,V>&> {};
            friend class const_iter;

            const_iter & begin () const;

    };

}

#endif

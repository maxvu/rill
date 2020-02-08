#ifndef RILL_MAP
#define RILL_MAP

#define RILL_MAP_DEFAULT_SIZE  8
#define RILL_MAP_RESIZE_FACTOR 2.0

namespace rill {

    template <typename K, typename V> class map {

        protected:

        struct slot {
            K _key
            V _val
        };

        buffer<slot>   _slots;
        unsigned long  _size;

        public:

        map ();
        map ( const map<K,V> & other );
        map ( unsigned long init_cap );
        map ( map<K,V> && other );

        unsigned long size () const;
        map<K,V> reserve ( unsigned long new_cap );
        map<K,V> compact ( unsigned long new_cap );

        bool has ( const K & key ) const;
        map<K,V> & set ( const K & key, const V & val );
        map<K,V> & unset ( const K & key );

        V & operator[] ( const K & key );
        const V & operator[] ( const K & key ) const;

        vector<K> keys () const;
        vector<V> vals () const;

        map<K,V> & clear ();

    };

}

#endif

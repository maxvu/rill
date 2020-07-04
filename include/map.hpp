#ifndef RILL_MAP
#define RILL_MAP

namespace rill {

    template <typename K, typename V> class map {

        public:
            class slot {
                K _key;
                V _val;
            };

        protected:
            array<slot> _slots;
            size_t      _size;

        public:
            map ( map length );
            map ( const map<K,V> & that );
            map ( map<K,V> && that );
            ~map ();

            map<K,V> & operator= ( const map<K,V> & that );
            map<K,V> & operator= ( map<K,V> && that );

            size_t size () const;
            size_t capacity () const;
            map<K,V> & reserve ( size_t new_capacity );
            map<K,V> & compact ();

            const V & operator[] ( const K & key ) const;
            T & operator[] ( size_t index );

            operator const T * () const;
            operator T * ();

    };

}

#endif

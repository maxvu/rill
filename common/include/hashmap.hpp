#ifndef RVM_HASHMAP
#define RVM_HASHMAP

#include "string.hpp"

#include <initializer_list>

namespace rill {

    template <typename T> class HashMap {

        public:

        struct Slot {
            String key;
            T      val;
        };

        protected:

        Slot * _slots;
        size_t _capacity;
        size_t _occupancy;

        public:

        HashMap ();
        HashMap ( const HashMap & other );
        HashMap ( HashMap && other );
        HashMap ( std::initializer_list<Slot> init_list );
        ~HashMap ();

        size_t size () const;
        double load () const;

        HashMap & reserve ( size_t new_capacity );
        HashMap & compact ();

        bool has ( const String & key ) const;
        HashMap & set ( const String & key, const T & val ) const;
        HashMap & unset ( const String & key ) const;

        T & operator[] ( const String & key );
        const T & operator[] ( const String & key ) const;

        HashMap operator<< ( const HashMap & that ) const;
        HashMap & operator<<= ( const HashMap & that );

        HashMap & clear ();

        class Iter {

            protected:

            HashMap _map;
            Slot *  _position;

            public:

            Iter ( HashMap & map );

            Iter & operator++ (int);
            operator bool () const;
            const String & key () const;
            T & value ();
            Iter & remove ();

        };

        Iter begin ();

        class ConstIter {

            protected:

            HashMap _map;
            Slot *  _position;

            public:

            Iter ( HashMap & map );

            Iter & operator++ (int);
            operator bool () const;
            const String & key () const;
            const T & value () const;

        };

        ConstIter begin () const;

    };

}

#endif

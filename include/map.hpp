#ifndef RILL_MAP
#define RILL_MAP

#include "string.hpp"
#include "vector.hpp"

namespace rill {

    template <typename T> class map {

        protected:

        struct slot {
            string _key;
            T _val;
        };

        vector<slot> _items;
        unsigned int _size;

        public:

        map ();
        map ( unsigned int initial_capacity );
        map ( const map<T> & other );
        map ( map<T> && other );
        ~map ();

        unsigned long size () const;
        operator bool () const;

        map<T> & reserve ( unsigned int new_capacity );
        map<T> & compact ();

        bool has ( const string & key ) const;
        const T & get ( const string & key ) const;
        T & get ( const string & key );
        map<T> & set ( const string & key, const T & val );
        map<T> & unset ( const string & key );

        vector<string> keys () const;
        vector<T> vals () const;

        map<T> merge ( const map<T> & other );

        bool operator== ( const map<T> & other ) const;
        bool operator!= ( const map<T> & other ) const;

        map<T> & operator= ( const map<T> & other );

        class iter;
        class const_iter;

        const_iter begin () const;
        iter begin ();

        map<T> & clear ();

        protected:

        template <typename M> class iter_base {

            protected:

            M map;

            public:

            iter_base ( M map );

            operator bool () const;
            iter_base<M> operator++ ();
            const T & operator* () const;
            const string & key () const;
            const T & val () const;

        };

        public:

        class const_iter : public iter_base<const map&> {

            public:
            const_iter ( const map & map );

        };

        class iter : public iter_base<map&> {

            public:

            iter ( map & map );
            T & val ();

        };

    };

};

#endif

#ifndef RILL_SET
#define RILL_SET

namespace rill {

    template <typename T> class set {

        protected:
        hashmap<T,bool> _map;

        set ();
        set ( const set<T> & that );

        bool has ( const T & item ) const;
        set<T> & set ( const T & item ) const;
        set<T> & unset ( const T & item ) const;


    };

}

#endif

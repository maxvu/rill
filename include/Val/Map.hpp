#ifndef RILL_VAL_MAP
#define RILL_VAL_MAP

#include "Val/Val.hpp"

#include <cstddef>
#include <unordered_map>

#define RILL_VAL_MAP_DEFAULTSIZE     8
#define RILL_VAL_MAP_MINSIZE         8
#define RILL_VAL_MAP_MAXLOAD         0.95
#define RILL_VAL_MAP_GROWTHC         2.00
#define RILL_VAL_MAP_LOADFN(OCC,CAP) ( double ) OCC / ( double ) CAP

namespace Rill {

class Map : public Refcounted {

    friend class Iter;
    friend class ConstIter;

    size_t hash_a ( const Buf & key ) const;
    size_t hash_b ( const Buf & key ) const;
    size_t hash_c ( const Buf & key ) const;
    size_t hash_d ( const Buf & key ) const;

    struct Slot {
        Val key;
        Val val;

        static void swap ( Slot & a, Slot & b );
        bool isVacant () const;
    };

    protected:

    Slot * slots;
    size_t occ;
    size_t cap;

    Map & resize ( size_t new_size );

    public:

    Map ();
    Map ( size_t init_cap );
    Map ( const Map & other );
    ~Map ();

    Val & get ( const Buf & key ) const;
    Map & set ( const Buf & key, const Val & val );
    bool has ( const Buf & key ) const;
    Map & unset ( const Buf & key );
    Map & clear ();

    size_t size () const;
    double load () const;

    Map & merge ( const Map & other );

    Val keys () const;
    Val vals () const;

    Map & reserve ( size_t new_cap );
    Map & compact ();
    operator bool () const;
    Val serialize () const;

    class Iter {

        protected:

        Map & map;
        size_t pos;

        public:

        Iter ( Map & map );

        Iter & operator++ (int);
        const Buf & key () const;
        Val & val ();
        Iter & remove ();
        operator bool () const;

    };

    class ConstIter {

        protected:

        const Map & map;
        size_t pos;

        public:

        ConstIter ( const Map & map );

        ConstIter & operator++ (int);
        const Buf & key () const;
        const Val & val ();
        operator bool () const;

    };

    Iter begin ();
    ConstIter begin () const;

};

}

#endif

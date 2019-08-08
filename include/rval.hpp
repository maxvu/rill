#ifndef RILL_VAL
#define RILL_VAL

namespace rill {

    template <typename T> class refcounted {
        protected:
        unsigned long _refcount;

        public:
        refcounted ();
        T & ref ();
        void deref ();
    };

    class rval;

    class rstr : public string, refcounted<rstr> {};
    class rvec : public vector<rval>, refcounted<rvec> {};
    class rmap : public hashmap<rval,rval>, refcounted<rmap> {};

    class rval {

        public:
        enum type {
            NIL = 0,
            IXX = 1,
            UXX = 2,
            FXX = 3,
            STR = 4,
            VEC = 5,
            MAP = 6,
            USR = 7
        };

        protected:
        type          _type : 3;
        unsigned long _tag  : 61;
        union {
            long          _ixx;
            unsigned long _uxx;
            double        _fxx;
            rstr *        _str;
            rvec *        _vec;
            rmap *        _map;
            void *        _usr;
        };

        public:
        rval ();
        rval ( const rval & that );
        rval ( long i );
        rval ( unsigned long u );
        rval ( double f );
        rval ( const string & that );
        rval ( const rvec & that );
        rval ( const rmap & that );
        ~rval ();

        type type () const;
        unsigned long tag () const;
        rval & tag ( unsigned long new_tag );

        rval & operator= ( const rval & that );

        long & as_ixx ();
        unsigned long & as_uxx ();
        double & as_fxx ();
        rstr & as_str ();
        rvec & as_vec ();
        rmap & as_map ();
        void * as_usr ();

        long as_ixx () const;
        unsigned long as_uxx () const;
        double as_fxx () const;
        const rstr & as_str () const;
        const rvec & as_vec () const;
        const rmap & as_map () const;
        const void * as_usr () const;

    };

}

#endif

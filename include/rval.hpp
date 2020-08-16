#ifndef RILL_RVAL
#define RILL_RVAL

namespace rill {

    class rval {

        protected:
        rval::type _typ : 3;
        UXX        _ref : RHEAD_REF_SIZE;
        UXX        _tag : RHEAD_TAG_SIZE;

        rval ( rval::type typ );
        rval ( rval::type typ, UXX tag );
        rval ( rval::type typ, UXX ref, UXX tag );

        rval & tag ( const UXX & tag );
        UXX    tag () const;

        bool ref ();
        bool deref ();
        UXX  get_ref () const;

    };

    class rref {

        public:
        union type {
            NIL = 0,
            IXX = 1,
            UXX = 2,
            FXX = 3,
            STR = 4,
            VEC = 5,
            MAP = 6,
            EXT = 7
        };

        protected:
        union {
            rnum * num;
            rstr * str;
            rvec * vec;
            rmap * map;
            rext * ext;
        };

        public:
        rref ( const rref & that );

        rref & operator= ( const rref & that );
        bool operator== ( const rref & that ) const;
        bool operator!= ( const rref & that ) const;

        type type () const;
        rnum & as_num ();
        rstr & as_str ();
        rvec & as_vec ();
        rmap & as_map ();
        rext & as_ext ();
        const rnum & as_num () const;
        const rstr & as_str () const;
        const rvec & as_vec () const;
        const rmap & as_map () const;
        const rext & as_ext () const;

        rref clone () const;
        rref & contains ( const rref & needle );
        rref & release ();

    };

    class rstr {

        protected:
        char * buf;
        UXX len;
        UXX cap;

        rstr ( UXX init_cap );
        ~rstr ();

        public:




    };

}

#endif

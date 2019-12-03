#ifndef RILL_VM_RVAL
#define RILL_VM_RVAL

#include "string.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "refcounted.hpp"
#include "vm/extension_type.hpp"

#ifdef RILL_32BIT
    #define RILL_TAG_SIZE 28
#else
    #define RILL_TAG_SIZE 60
#endif

namespace rill {
namespace vm {

    class rval;

    class rstr : public string, public refcounted<rstr> {};
    class rvec : public vector<rval>, public refcounted<rstr> {};
    class rmap : public map<rval>, public refcounted<rstr> {};

    class rval {

        public:

        enum type {
            NIL = 0, // nil
            ISO = 1, // instruction offset
            IXX = 2, // signed integer
            UXX = 3, // unsigned integer
            FXX = 4, // floating-point number
            STR = 5, // string
            VEC = 6, // vector
            MAP = 7, // hash map
            EXT = 8  // extension type
        };

        protected:

        unsigned int  _type : 4;
        unsigned long _tag  : RILL_TAG_SIZE;

        union {
            long             _ixx;
            unsigned long    _uxx;
            double           _fxx;
            rstr *           _str;
            rvec *           _vec;
            rmap *           _map;
            extension_type * _ext;
        };

        public:

        rval ();
        rval ( const rval & other );
        ~rval ();

        type type ();
        unsigned long tag () const;
        rval & tag ( unsigned long tag );
        bool is_fixed_width () const;

        long & as_ixx ();
        unsigned long & as_uxx ();
        double & as_fxx ();
        rstr & as_str ();
        rvec & as_vec ();
        rmap & as_map ();

        rval & compact ();
        bool contains ( const rval & needle ) const;
        rval clone () const;
        rval & exclude () const;

        rval & operator= ( const rval & other );
        bool operator== ( const rval & other );
        bool operator!= ( const rval & other );

        rval & set_nil ();

    };

}
}

#endif

#ifndef RILL_RVAL
#define RILL_RVAL

#include "string.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "refcounted.hpp"

#ifdef RILL_32BIT
    #define RILL_TAG_SIZE 29
#else
    #define RILL_TAG_SIZE 61
#endif

namespace rill {
    
    class rval;
    
    class rstr : public string, public refcounted {};
    class rvec : public vector<rval>, public refcounted {};
    class rmap : public map<rval>, public refcounted {};
    
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
            EXT = 7
        };
        
        protected:
        
        unsigned int  _type : 3;
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

#endif
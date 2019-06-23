#ifndef RILL_VM_RVAL
#define RILL_VM_RVAL

#include "string.hpp"
#include "vector.hpp"
#include "hashmap.hpp"
#include "refcounted.hpp"

namespace rill {

    enum rval_type {
       NIL,
       IXX,
       UXX,
       FXX,
       STR,
       VEC,
       MAP,
       UDO
   };

    class rstr : public string, public refcounted<rstr> {};
    class rvec : public vector<rval>, public refcounted<rvec> {};
    class rmap : public hashmap<rval>, public refcounted<rmap> {};

    class rval {

        protected:
        unsigned int _info;
        union {
            int          _ixx;
            unsigned int _uxx;
            double       _fxx;
            rstr *       _str;
            rvec *       _vec;
            rmap *       _map;
            void *       _udo;
        };

        public:
        static rval nil ();
        static rval ixx ( int i );
        static rval uxx ( unsigned int i );
        static rval fxx ( double i );
        static rval str ();
        static rval str ( unsigned int initial_capacity );
        static rval vec ();
        static rval vec ( unsigned int initial_capacity );
        static rval map ();
        static rval map ( unsigned int initial_capacity );

        rval ();
        rval ( const rval & that );
        rval ( rval && that );
        ~rval ();

        rval & operator= ( const rval & that );
        rval & operator= ( rval && that );

        rval_type type () const;
        unsigned int subtype () const;
        rval & subtype ( unsigned int new_subtype );

        bool equals ( const rval & val );
        bool cycles_to ( const rval & val ) const;
        rval clone ( const rval & val ) const;

        int & ixx ();
        unsigned int & uxx ();
        double & fxx ();
        rstr & str ();
        rvec & vec ();
        rmap & map ();

    };

}

#endif

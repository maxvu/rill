#ifndef RILL_VAL
#define RILL_VAL

#include "platform.h"

namespace rill {

    class string;
    template <typename T> class vector;
    template <typename K, typename V> class map;
    class strval;
    class vecval;
    class extval;

    enum rval_type {
        RVT_NIL,
        RVT_IXX,
        RVT_UXX,
        RVT_FXX,
        RVT_STR,
        RVT_VEC,
        RVT_MAP,
        RVT_EXT
    };

    class collectable {

        protected:


    };

    class rval {

        private:

            int  _type : 3;
            int  _tag  : TAG_SIZE;

            union {
                IXX      ixx;
                UXX      uxx;
                FXX      fxx;
                strval * str;
                vecval * vec;
                mapval * map;
            };

        protected:

            rval ( rval_type type );
            rval ( rval_type type, size_t tag );

        public:

            operator bool () const;
            bool operator== ( const rval * that ) const;
            bool operator!= ( const rval * that ) const;

    };

    class strval : public rval, public string {

        public:
            strval ();
            strval ( size_t init_cap );
            strval ( const char * cstr );
            strval ( const string & that );
            strval ( string && that );
            strval ( const strval & that );
            strval ( strval && that );

    };

    class vecval : public rval, public vector<rval*> {

        public:
            vecval ();
            vecval ( size_t init_cap );
            vecval ( const vector<rval*> & that );
            vecval ( vector<rval*> && that );
            vecval ( const vecval & that );
            vecval ( vecval && that );

    };

    class mapval : public rval, public map<string,rval*> {

        public:
            mapval ();
            mapval ( size_t init_cap );
            mapval ( const map<strval,rval*> & that );
            mapval ( map<strval,rval*> && that );
            mapval ( const mapval & that );
            mapval ( mapval && that );

    };

    class extval : public rval {

        virtual operator bool () const;
        virtual bool operator== ( const rval & that ) const;
        bool operator!= ( const rval & that ) const;
        virtual ~extval () =0;

    };


}

#endif

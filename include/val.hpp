#ifndef RILL_VAL
#define RILL_VAL

#include "platform.h"

namespace rill {

    class string;
    template <typename T> class vector;
    template <typename K, typename V> class map;

    enum rval_type {
        RVT_NUM,
        RVT_STR,
        RVT_VEC,
        RVT_MAP,
        RVT_EXT
    };

    class rval {

        private:

            int  _type : 3;
            int  _ref  : REF_SIZE;
            int  _tag  : TAG_SIZE;

        protected:

            rval ( rval_type type );
            rval ( rval_type type, size_t tag );

        public:

            rval & lease ();
            rval & release ();
            bool references ( rval * needle ) const;

            void compact ();

            operator bool () const;
            bool operator== ( const rval * that ) const;
            bool operator!= ( const rval * that ) const;

    };

    class numval : public rval {

        protected:
            union {
                IXX i;
                UXX u;
                FXX f;
            };

        public:
            numval ( IXX i );
            numval ( UXX u );
            numval ( FXX f );

            IXX & as_i ();
            UXX & as_u ();
            FXX & as_f ();

            const IXX & as_i () const;
            const UXX & as_u () const;
            const FXX & as_f () const;

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

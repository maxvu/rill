#ifndef RILL_VAL
#define RILL_VAL

namespace rill {

    class string;
    template <typename T> class vector;
    template <typename K, typename V> class map;

    enum rval_type {
        IXX,
        UXX,
        FXX,
        STR,
        VEC,
        MAP,
        EXT
    };

    template <typename V> class rval {

        private:

            size_t _head;
            size_t _ref;

        protected:

            rval ( rval_type type );
            rval ( rval_type type, size_t tag );

        public:

            V & lease ();
            V & release ();
            bool references ( rval * needle ) const;

            V & compact ();

            operator bool () const;
            bool operator== ( const rval * that ) const;
            bool operator!= ( const rval * that ) const;

    };

    class numval : public rval<numval> {

        protected:
            union {
                long i;
                unsigned long u;
                double f;
            };

        public:
            numval ( long i );
            numval ( unsigned long i );
            numval ( double f );

            long & as_i ();
            unsigned long & as_u ();
            double & as_f ();

            const long & as_i () const;
            const unsigned long & as_u () const;
            const double & as_f () const;

    };

    class strval : public rval<strval>, public string {

        public:
            strval ();
            strval ( size_t init_cap );
            strval ( const char * cstr );
            strval ( const string & that );
            strval ( string && that );
            strval ( const strval & that );
            strval ( strval && that );

            operator string & ();
            operator const string & () const;

    };

    class vecval : public rval<vecval>, public vector<rval*> {

        public:
            vecval ();
            vecval ( size_t init_cap );
            vecval ( const vector<rval*> & that );
            vecval ( vector<rval*> && that );
            vecval ( const vecval & that );
            vecval ( vecval && that );

            operator vector<rval*> & ();
            operator const vector<rval*> & () const;

    };

    class mapval : public rval<mapval>, public map<string,rval*> {

        public:
            mapval ();
            mapval ( size_t init_cap );
            mapval ( const map<strval,rval*> & that );
            mapval ( map<strval,rval*> && that );
            mapval ( const mapval & that );
            mapval ( mapval && that );

            operator map<strval,rval*> & ();
            operator const map<strval,rval*> & () const;

    };

    class extval : public rval<extval> {

        virtual operator bool () const;
        virtual bool operator== ( const rval & that ) const;
        bool operator!= ( const rval & that ) const;
        virtual ~extval () =0;

    };


}

#endif

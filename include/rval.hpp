#ifndef RILL_RVAL
#define RILL_RVAL

namespace rill {
namespace rval {

    enum rval_type {
        NIL = 0,
        UXX = 1,
        IXX = 2,
        FXX = 3,
        STR = 4,
        VEC = 5,
        MAP = 6,
        UDO = 7
    };

    class rval_header {

        protected:
        unsigned int _value;

        public:
        rval_header ()

        rval_type type () const;
        rval_header & type ( rval_type new_type );

        unsigned int tag () const;
        rval_header & tag ( unsigned int new_tag );

    };

    template <typename T> class rval {

        protected:
        rval_header _header;

        public:
        rval ();

        protected:
        rval_type & type ();
        unsigned int tag ();
        rval * clone () const;
        bool contains ( const rval * that );

    };

    class rnil : public rval<rnil> {

        public:
        rnil();

    };

    class rixx : public rval<rixx> {

        protected:
        int _i;

        public:
        rixx ();

        operator int & ();
        operator const int & () const;

    };

    class ruxx : public rval<ruxx> {

        protected:
        unsigned int _u;

        public:
        ruxx ();

        operator unsigned int & ();
        operator const unsigned int & () const;

    };

    class rfxx : public rval<ruxx> {

        protected:
        double _f;

        public:
        rfxx ();

        operator double & ();
        operator const double & () const;

    };

    class rvec : public rval<rvec>, public vector<rval*> {

        public:
        rvec ();
        rvec ( const rvec & that );

    };

    class rmap : public rval<rmap>, public rmap<string,rval*> {

        public:
        rmap ();
        rmap ( const rmap & that );

    };

}
}

#endif

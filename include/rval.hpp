#ifndef RILL_RVAL
#define RILL_RVAL

#define RILL_RVAL_TYP_LENGTH 3

#ifdef RILL_32BIT
    #define RILL_RVAL_TAG_LENGTH 29
#endif

#ifdef RILL_64BIT
    #define RILL_RVAL_TAG_LENGTH 61
#endif

namespace rill {

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

    class refcounted {

        public:

        refcounted ();

    };

    class rval {

        protected:

        rval_type    _type : 3;
        unsigned int _tag  : RILL_RVAL_TAG_LENGTH;
        unsigned int _ref;

        union {
            unsigned int   _uxx;
            int            _ixx;
            double         _fxx;
            string *       _str;
            vector<rval> * _vec;
            map<rval> *    _map;
        };

        public:

        rval ();

    };

}

#endif

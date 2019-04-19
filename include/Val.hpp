#ifndef RILL_VAL
#define RILL_VAL

namespace Rill {

    enum ValType {
        NIL = 0,
        IXX = 1,
        UXX = 2,
        FXX = 3,
        BUF = 4,
        VEC = 5,
        MAP = 6
    };

    class Buffer;
    class Vector;
    class Map;

    class Val {

        protected:

        ValType typ;
        union {
            int           ixx;
            unsigned int  uxx;
            double        fxx;
            Buffer *      buf;
            Vector<Val> * vec;
            Map<Val> *    map;
        };

        Val ();
        Val ( const Val & that );
        ~Val ();

    };

    class IxxVal : public Val {

        operator int & ();
        operator const int & () const;

    };

}

#endif

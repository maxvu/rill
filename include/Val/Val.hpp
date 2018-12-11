#ifndef RILL_VAL_VAL
#define RILL_VAL_VAL

namespace Rill {

    class Val {

        public:

        virtual ~Val () =0;

        virtual Val & lease () =0;
        virtual int release () =0;
        virtual Val & exclude () =0;
        virtual Val * clone () const =0;

        virtual operator bool () const =0;
        virtual bool operator==  ( const Val & other ) =0;
        bool operator!=  ( const Val & other );

        virtual bool contains ( const Val * needle ) =0;
        // void dump () =0;

    };

}

#endif

#ifndef RILL_ERROR
#define RILL_ERROR

#define RILL_ERROR_MESSAGE_LENGTH 128

namespace Rill {

    class Error {

        protected:
        char * msg;

        public:
        Error ();
        Error ( const char * message );
        const char * message () const;

    };

    class OOMError : public Error {

        public:
        OOMError ();
        const char * message () const;

    };

    class OOBError : public Error {

        public:
        OOBError ();
        const char * message () const;

    };

    class ArgError : public Error {

        public:
        ArgError ( const char * target, const char * arg_name );

    };

}

#endif

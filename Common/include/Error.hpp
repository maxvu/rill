#ifndef RILL_ERROR
#define RILL_ERROR

#include <cstddef>

#define RILL_ERROR_MESSAGE_LENGTH 128

namespace Rill {

    class UTF8String;

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

    class UTF8Error : public Error {

        protected:
        UTF8String & source;
        size_t index;

        public:
        UTF8Error ( const UTF8String & utf8_string, size_t index );

    };

}

#endif

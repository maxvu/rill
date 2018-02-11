#ifndef RILL_ERROR
#define RILL_ERROR

#include <cstring>

namespace Rill {

    class Error {

        protected:

        char * msg;

        public:

        Error ( const char * msg );
        ~Error();

        const char * getMessage ();

    };

    class InternalError : public Error {

        protected:

        const char * msg;

        public:

        InternalError ( const char * msg );

    };

};

#endif

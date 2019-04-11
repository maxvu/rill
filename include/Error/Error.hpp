#ifndef RILL_ERROR_ERROR
#define RILL_ERROR_ERROR

namespace Rill {
namespace Error {

    class Error {

        virtual const char * message () const;

    };
    
}
}

#endif

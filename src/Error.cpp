#include "Error.hpp"

namespace Rill {

    Error::Error ( const char * msg ) {
        this->msg = new char[ strlen( msg ) + 1 ];
        strcpy( this->msg, msg );
    }

    Error::~Error () {
        delete[] this->msg;
    }

    const char * Error::getMessage () {
        return this->msg;
    }

    InternalError::InternalError ( const char * msg ) : Error( msg ) {

    }

};

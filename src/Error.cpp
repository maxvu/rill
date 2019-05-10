#include <cstdio>
#include <cstring>

#include "Error.hpp"
#include "Memory.hpp"

namespace Rill {

Error::Error () : msg( nullptr ) {

}

Error::Error ( const char * message ) : msg( nullptr ) {
    this->msg = allocate<char>( RILL_ERROR_MESSAGE_LENGTH );
    strcpy( this->msg, message );
}

const char * Error::message () const {
    if ( !this->msg )
        return "error";
    return this->msg;
}

OOMError::OOMError () : Error( nullptr ) {

}

const char * OOMError::message () const {
    return "out of memory";
}


OOBError::OOBError () : Error( nullptr ) {

}

const char * OOBError::message () const {
    return "out of bounds";
}


ArgError::ArgError ( const char * target, const char * arg_name ) {
    this->msg = allocate<char>( RILL_ERROR_MESSAGE_LENGTH );
    if ( this->msg )
        snprintf(
            this->msg,
            RILL_ERROR_MESSAGE_LENGTH,
            "'%s' was given a bad value for '%s'",
            target,
            arg_name
        );
}

}

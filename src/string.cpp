#include <algorithm>
#include <cstring>

#include "string.hpp"
#include "error.hpp"
#include "alloc.hpp"

namespace rill {

    void string::terminate () {
        _buffer[ _length - 1 ] = 0;
    }

    string::string () : _buffer( DEFAULT_SIZE ) {}
    string::string ( size_t length )
        : _buffer( length ),
          _length( length ) {
            terminate();
        }

    string::string ( const char * that ) : string( strlen( that ) ) {
        std::copy( that, that + _length - 1, _buffer );
        terminate();
    }

    string::string ( const string & that ) : string( that._length ) {
        std::copy( that.begin(), that.end(), begin() );
        terminate();
    }

}

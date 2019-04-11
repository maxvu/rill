#ifndef RILL_ERROR_NULLARGUMENTERROR
#define RILL_ERROR_NULLARGUMENTERROR

namespace Rill {
namespace Error {

    class NullArgumentError : public Error {

        public:

        NullArgumentError();

        const char * getMessage () const;

    };

}
}

#endif

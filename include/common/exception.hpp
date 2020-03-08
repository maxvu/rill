#ifndef RILL_EXCEPTION
#define RILL_EXCEPTION

#include <exception>

namespace rill {

    class ArgException : public std::exception {
        public:
            const char * what () const noexcept override;
    };

}

#endif

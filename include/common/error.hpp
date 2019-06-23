#ifndef RILL_ERROR
#define RILL_ERROR

#include <exception>

namespace rill {

    class error_base : public std::exception {};

    class error : public error_base {

        protected:
        const char * _msg;

        public:
        error ( const char * msg );
        ~error ();
        const char * what () const noexcept;

    };

    class system_error : public error_base {};
    class user_error   : public error_base {};

    class oom_error : public system_error {

        public:
        const char * what () const noexcept;

    };

    class oob_error : public user_error {

        public:
        const char * what () const noexcept;

    };

    class arg_error : public user_error {

        public:
        const char * what () const noexcept;

    };

    class utf8_error : public user_error {};

    class invalid_byte_error : public utf8_error {

        public:
        invalid_byte_error ( unsigned int position );

        const char * what () const noexcept;

    };

    class early_termination_error : public utf8_error {

        public:
        early_termination_error ();

        const char * what () const noexcept;

    };

}

#endif

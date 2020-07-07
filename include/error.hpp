#ifndef RILL_ERROR
#define RILL_ERROR

namespace rill {

    /*

    */

    class error {

        public:
            const char * what () const;

    };

    /*

    */

    class internal_error : public error {
        protected:
            internal_error() {}
    };

    class arg_error : public internal_error {
        public:
            arg_error() {}
            const char * what () const {
                return "bad argument";
            }
    };

    class usage_error : public internal_error {
        public:
            usage_error() {}
            const char * what () const {
                return "invalid usage";
            }
    };

    /*

    */

    class system_error : public error {
        protected:
            system_error () {}
    };

    class oom_error : public system_error {
    public:
            oom_error () {}
            const char * what () const {
                return "out of memory";
            }
    };

    // class user_error : public error {};

}

#endif

#ifndef RILL_UNIT
#define RILL_UNIT

namespace rill {
namespace lang {

    class unit {

        public:
        virtual const string & name () const =0;

    };

    class file_unit {

        protected:
        string _name;
        FILE * _file;

        public:
        file_unit ( const string & location );
        ~file_unit ();

        const string & name ();
        operator bool () const;
        file_unit & operator++ (int);
        int peek () const;

    };

    class unit_stdin {};
    class unit_repl {};

}
}

#endif

#ifndef RILL_TEST
#define RILL_TEST

#include <string>
#include <vector>

namespace rill {

    class assertion {

        protected:
        std::string   _text;
        std::string   _file;
        unsigned long _line;
        bool          _ok;

        assertion (
            bool condition,
            std::string   text,
            std::string   file,
            unsigned long line,
        ) :
            _text( text ),
            _file( file ),
            _line( line ),
            _ok( condition ) {}

        const std::string & text () const { return _text; }
        const std::string & file () const { return _file; }
        unsigned long line () const { return _line; }
        bool ok () const { return _ok; }

    };

    class test {

        protected:
        std::string _name;
        std::vector<assertion> _assertions;

        public:
        test ( const std::string & name ) : _name( name ) {}

        std::vector<assertion> & assertions () { return _assertions; }

        bool passing () const {
            for ( auto it = assertions.begin(); it != assertions.end(); it++ ) {
                if ( !it->ok() )
                    return false;
                it++;
            }
            return true;
        }

    };

#define TEST(name) { test curr;
#define MUST(cond) curr.assertions.push( assertion(cond, #cond, __FILE__, __LINE__ ) );
#define END }

#define DEBUG raise( SIGINT );

}

#endif

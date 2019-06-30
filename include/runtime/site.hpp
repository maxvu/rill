#ifndef RILL_LANG_SITE
#define RILL_LANG_SITE

namespace rill {
namespace lang {

    class site {

        protected:
        string        _source;
        unsigned long _line;
        unsigned long _offset;

        public:

        site (
            const string & source,
            unsigned long line,
            unsigned long offset
        );

        const string & source () const;
        unsigned int line () const;
        unsigned int offset () const;

    };

}
}

#endif

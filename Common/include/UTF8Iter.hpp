#ifndef RILL_UTF8ITER
#define RILL_UTF8ITER

namespace Rill {

    class UTF8Iter {

        protected:

        const uint8_t * cur;
        const uint8_t * end;
        int             cdp;
        uint8_t         run;

        public:

        UTF8Iter ( const uint8_t * begin, const uint8_t * end );

        operator bool () const;
        UTF8Iter & operator++ ();
        UTF8Iter operator++ ( int ) const;
        int codepoint () const;

    };

}

#endif

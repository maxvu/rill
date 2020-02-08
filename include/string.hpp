#ifndef RILL_VECTOR
#define RILL_VECTOR

#define RILL_STRING_DEFAULT_SIZE  8
#define RILL_STRING_RESIZE_FACTOR 2.0

namespace rill {

    class string {

        protected:
        char *        _buffer;
        unsigned long _size;
        unsigned long _capacity;

        public:
        string ();
        string ( unsigned long init_cap );
        string ( const string & other );
        string ( string && other );
        ~string ();

        unsigned long length ();
        string & reserve ( unsigned long new_cap );
        string & compact ();

        bool operator== ( const string & other ) const;
        bool operator!= ( const string & other ) const;

        string operator+ ( const string & other ) const;
        string operator+= ( const string & other ) const;

        operator const char * () const;
        string substr ( unsigned long begin, unsigned long length ) const;

        string & reverse ();
        string & clear ();

    };

}

#endif

#ifndef RILL_STRING
#define RILL_STRING

namespace rill {

    class string {

        protected:
        char *       _buffer;
        unsigned int _length;
        unsigned int _capacity;

        public:
        string ();
        string ( unsigned int initial_capacity );
        string ( const string & other );
        string ( string && other );
        string ( const char * cstr );
        ~string ();

        unsigned long size () const;
        operator bool () const;

        string & reserve ( unsigned int new_capacity );
        string & compact ();

        operator const char * () const;
        operator char * ();

        char & operator[] ( unsigned int index );
        char operator[] ( unsigned int index ) const;

        string operator+ ( const string & other ) const;
        string & operator+= ( const string & other );

        string & operator= ( const string & other );
        string & operator= ( const char * str );

        bool operator== ( const string & other ) const;
        bool operator!= ( const string & other ) const;

        string & clear ();

    };

};

#endif

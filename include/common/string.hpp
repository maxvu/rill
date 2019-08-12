#ifndef RILL_STRING
#define RILL_STRING

namespace rill {

    class string {

        public:
        static unsigned long MINIMUM_SIZE;
        static unsigned long DEFAULT_SIZE;
        static double        GROWTH_RATE;

        protected:
        char * _buffer;
        unsigned long _length;
        unsigned long _capacity;

        string resize ( unsigned long new_capacity );

        public:
        string ();
        string ( unsigned long initial_capacity );
        string ( const string & that );
        string ( string && that );
        string ( const char * that );
        ~string ();

        unsigned long length () const;

        string & reserve ( unsigned long new_capacity );
        string & compact ();

        char & operator[] ( unsigned long index );
        char operator[] ( unsigned long index ) const;

        operator bool () const;
        operator const char * () const;
        operator unsigned char * () const;

        string & operator+= ( const char * that );
        string & operator+= ( const string & that );

        bool operator== ( const string & that ) const;
        bool operator!= ( const string & that ) const;
        bool operator== ( const char * that ) const;
        bool operator!= ( const char * that ) const;

        string & operator= ( const string & that );
        string & operator= ( const char * that );
        string operator+ ( const string & that ) const;
        string operator+ ( const char * that ) const;

        string & clear ();

    };

}

#endif

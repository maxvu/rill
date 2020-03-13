#ifndef RILL_STRING
#define RILL_STRING

namespace rill {

    class string {

        protected:
            buffer<char> _buffer;
            size_t       _len;

            string & terminate ();

        public:
            string ();
            string ( size_t init_len );
            string ( const char * cstr );
            string ( const string & that );
            string ( string && that );
            ~string ();

            size_t length () const;
            string & reserve ( size_t new_cap );
            string & compact ();

            string & operator= ( const string & that );
            string & operator= ( string && that );

            string & operator+= ( const string & that );
            bool operator== ( const string & that ) const;
            bool operator!= ( const string & that ) const;

            string & operator+= ( const char * that );
            bool operator== ( const char * that ) const;
            bool operator!= ( const char * that ) const;

            operator const char * () const;
            char & operator[] ( size_t index );
            char operator[] ( size_t index ) const;

            string & clear ();

    };

}

#endif

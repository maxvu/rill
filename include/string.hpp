#ifndef RILL_STRING
#define RILL_STRING

namespace rill {

    class string {

        public:
            constexpr size_t DEFAULT_SIZE = 31;
            constexpr float  GROWTH_RATE  = 2.0;

        protected:
            array<char> _chars;
            size_t      _length;

        public:
            string ( size_t length );
            string ( const char * that );
            string ( const array<T> & that );
            string ( string && that );
            ~string ();

            string & operator= ( const string & that );
            string & operator= ( string && that );
            string & operator= ( const char * that );

            string & operator== ( const string & that ) const;
            string & operator!= ( const string & that ) const;
            string & operator== ( const char * that ) const;
            string & operator!= ( const char * that ) const;

            string & operator+= ( const string & that ) const;
            string & operator+= ( const char * that ) const;

            string operator+ ( const string & that ) const;
            string operator+ ( const char * that ) const;

            size_t length () const;
            size_t capacity () const;

            string & reserve ( size_t new_capacity );
            string & compact ();

            char operator[] ( size_t index ) const;
            char & operator[] ( size_t index );

            operator const char * () const;
            operator char * ();

            string substr ( size_t start, size_t len ) const;
            string & clear ();

    };

}

#endif

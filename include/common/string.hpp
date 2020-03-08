#ifndef RILL_STRING
#define RILL_STRING

namespace rill {

    class String {

        protected:
            Buffer buffer;

        public:
            String ();
            String ( size_t init_cap );
            String ( const char * cstr );
            String ( const String & that );
            String ( String && that );

            operator const char * () const;
            char & operator[] ( size_t index );
            char operator[] ( size_t index ) const;
            bool is_empty () const;
            size_t length () const;

            String & reserve ( size_t new_cap );
            String & compact ();

            String & operator= ( const String & that );
            String & operator= ( String && that );

            bool operator< ( const String & that ) const;
            bool operator== ( const String & that ) const;
            bool operator!= ( const String & that ) const;

            String & operator+= ( const String & that );
            String & operator+= ( const char * cstr );

            String & append ( const String & that );
            String & append ( const char * cstr );
            String & append ( const unsigned char * bytes, size_t bytes_len );

            String operator+ ( const String & that );
            String operator+ ( const char * cstr );

            String substr ( size_t start, size_t length ) const;

            String & clear ();

    };

}

#endif

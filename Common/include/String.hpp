#ifndef RILL_STRING
#define RILL_STRING

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "UTF8Iter.hpp"

#define RILL_STRING_DEFAULT_SIZE 16
#define RILL_STRING_MINIMUM_SIZE 8
#define RILL_STRING_GROWTH_RATE  2.0

namespace Rill {

    class String {

        protected:

        size_t len;
        Buffer buf;

        String & resize ( size_t new_length );
        String & terminate ();

        public:

        String ();
        String ( size_t initial_capacity );
        String ( const char * cstr );
        String ( const String & that );
        ~String ();

        Buffer & buffer ();
        const Buffer & buffer () const;
        operator const char * () const;

        String & reserve ( size_t new_capacity );
        String & compact ();

        String operator+ ( const String & that ) const;
        String & operator+= ( const String & that );
        String & operator= ( const String & that );
        bool operator< ( const String & that ) const;
        bool operator== ( const String & that ) const;
        bool operator!= ( const String & that ) const;

        String operator+ ( const char * that ) const;
        String & operator+= ( const char * that );
        String & operator= ( const char * that );
        bool operator< ( const char * that ) const;
        bool operator== ( const char * that ) const;
        bool operator!= ( const char * that ) const;

        String & clear ();
        String & reverse ();
        const UTF8Iter & asUTF8 () const;

    };

}

#endif

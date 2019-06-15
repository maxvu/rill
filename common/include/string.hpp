#ifndef RVM_STRING
#define RVM_STRING

#include <cstddef>

namespace rill {

    class String {

        protected:

        char * _buffer;
        size_t _length;
        size_t _capacity;

        String & nullTerminate ();

        public:

        static const size_t MIN_SIZE;
        static const size_t DEFAULT_SIZE;
        static const float  GROWTH_RATE;

        String ();
        String ( size_t initial_capacity );
        String ( const String & that );
        String ( const char * cstr );
        String ( String && that );
        ~String ();

        String & reserve ( size_t new_capacity );
        String & compact ();

        size_t length () const;
        operator const char * () const;
        operator char * ();

        String & operator= ( const String & that );
        String & operator= ( const char * cstr );

        bool operator== ( const String & that ) const;
        bool operator!= ( const String & that ) const;
        bool operator== ( const char * cstr ) const;
        bool operator!= ( const char * cstr ) const;

        String operator+ ( const String & that ) const;
        String operator+ ( const char * cstr ) const;
        String operator+= ( const String & that );
        String operator+= ( const char * cstr );

        String & clear ();

    };

}

#endif

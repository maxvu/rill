#ifndef RILL_STRING
#define RILL_STRING

#include "vector.hpp"

#include <cstddef>
#include <cstdint>

namespace rill {

    class char_string;
    class byte_string;
    class utf8_iter;

    class string {

        protected:
        vector<char>   _buffer;
        unsigned long  _length;
        unsigned long  _capacity;

        public:

        string ();
        string ( unsigned long initial_capacity );
        string ( const string & that );
        string ( const string && that );
        ~string ();

        unsigned long length () const;
        string & reserve ( unsigned long new_capacity );
        string & compact ();

        string & operator= ( const string & that );
        string & operator= ( string && that );
        string & operator+= ( const string & that );
        string operator+ ( const string & that ) const;
        bool operator== ( const string & that ) const;
        bool operator!= ( const string & that ) const;

        char_string & as_char ();
        const char_string & as_char () const;

        byte_string & as_bytes ();
        const byte_string & as_bytes () const;

        utf8_iter as_utf8 () const;

    };

    class char_string : public string {

        protected:
        char_string();

        public:
        char_string ( const char * cstr );

        operator char * ();
        operator const char * () const;

        string operator+ ( const char * cstr ) const;
        string & operator+= ( const char * cstr );
        bool operator== ( const char * cstr ) const;
        bool operator!= ( const char * cstr ) const;
        char & operator[] ( unsigned long index );
        char operator[] ( unsigned long index ) const;

    };

    class byte_string : public string {

        protected:
        byte_string();

        public:
        byte_string ( uint8_t * mem, unsigned long mem_length );

        operator uint8_t * ();
        operator const uint8_t * () const;

        uint8_t & operator[] ( unsigned long index );
        uint8_t operator[] ( unsigned long index ) const;

    };

    class utf8_iter {

        protected:
        const string & _string;
        unsigned long  _position;
        int            _codepoint;
        char           _codepoint_length;

        public:

        utf8_iter ( const string & string );

        operator bool () const;
        utf8_iter operator++ ( int );
        int codepoint ();

    };

}

#endif

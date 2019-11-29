#ifndef RILL_STRING
#define RILL_STRING

#include "slab.hpp"

namespace rill {

    class string {
        
        protected:
            
        char * _buffer;
        unsigned long _length;
        
        public:
        
        string ();
        string ( const string & other );
        string ( const char * cstr );
        string ( string && other );
        
        unsigned long length () const;
        operator char * () const;
        
        string & reserve ( unsigned long new_capacity );
        string & compact ();
        
        string & operator= ( const string & other );
        string & operator= ( const char * cstr );
        string & operator= ( string && other );
        
        char & operator[] ( unsigned long index );
        char operator[] ( unsigned long index ) const;
        
        string & operator+= ( const string & other );
        string & operator+= ( const char * cstr );
        string operator+ ( const string & other );
        string operator+ ( const char * cstr );
        
        bool operator== ( const string & other ) const;
        bool operator== ( const char * cstr ) const;
        
        bool operator!= ( const string & other ) const;
        bool operator!= ( const char * cstr ) const;
        bool operator> ( const string & other ) const;
        bool operator> ( const char * cstr ) const;
        bool operator< ( const string & other ) const;
        bool operator< ( const char * cstr ) const;
        bool operator<= ( const string & other ) const;
        bool operator<= ( const char * cstr ) const;
        bool operator>= ( const string & other ) const;
        bool operator>= ( const char * cstr ) const;
        
        string substr ( unsigned long start ) const;
        string substr ( unsigned long start, unsigned long length ) const;
        
        string & clear ();
        
    };

}

#endif
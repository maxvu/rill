#ifndef RILL_VECTOR
#define RILL_VECTOR

#include <initializer_list>

namespace rill {

    template <typename T> class vector {
        
        protected:
            
        T * _items;
        unsigned long _size;
        
        public:
        
        vector ();
        vector ( unsigned long size );
        vector ( const vector<T> & other );
        vector ( vector && other );
        vector ( std::initializer_list<T> init_list );
        
        vector<T> & reserve ( unsigned long new_capacity );
        vector<T> & compact ();
        
        T & operator[] ( unsigned long index );
        const T & operator[] ( unsigned long index ) const;
        
        unsigned long length () const;
        
        vector<T> & operator+= ( const vector<T> & other );
        vector<T> & operator= ( const vector<T> & other );
        vector<T> & operator= ( vector<T> && other );
        
        bool operator== ( const vector<T> & other ) const;
        bool operator!= ( const vector<T> & other ) const;
        
        vector<T> & push ( const T & item );
        vector<T> & pop ();
        
        vector<T> & unshift ( const T & item );
        vector<T> & shift ();
        
        vector<T> & fill ( const T & item, unsigned long n );
        
        vector<T> & clear ();
        
    };

}

#endif
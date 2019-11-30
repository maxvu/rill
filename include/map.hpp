#ifndef RILL_MAP
#define RILL_MAP

#include <initializer_list>

#include "string.hpp"

namespace rill {

    template <typename T> class map {
        
        protected:
            
        struct slot {
            string _key;
            T      _val;
        };
            
        slot *        _slots;
        unsigned long _size;
        unsigned long _capacity;
        
        public:
        
        map ();
        map ( unsigned long init_size );
        map ( const map & other );
        map ( map && other );
        map ( std::initializer_list<T> init_list );
        
        unsigned long size () const;
        
        map<T> & reserve ( unsigned long new_capacity );
        map<T> & compact ();
        
        T & operator[] ( const string & key );
        const T & operator[] ( const string & key ) const;
        
        bool has ( const string & key ) const;
        const T & get ( const string & key ) const;
        T & get ( const string & key );
        map<T> & remove ( const string & key );
        
        map<T> & operator= ( const map<T> & other );
        map<T> & operator= ( map<T> && other );
        
        vector<string> keys () const;
        vector<T> vals () const;
        map<T> & subsume ( const map<T> & other );
        
        map<T> & clear ();
        
        protected:
            
        template <typename M> class iter_base {
            
            protected:
                
            M map;
            unsigned long index;
            
            public:
            
            void operator++ ( int );
            const string & key () const;
            const T & val () const;
            operator bool () const;
            
        };
        
        public:
            
        class iter : public iter_base< map<T> & > {
            
            public:
                
            iter ( map<T> & map );
            
            T & val ();
            iter & remove ();
            
        };
        
        class const_iter : public iter_base< const map<T> & > {
        
            public:
                
            const_iter ( const map<T> & map );
        
        };
        
        const_iter begin () const;
        iter begin ();
        
    };

}

#endif
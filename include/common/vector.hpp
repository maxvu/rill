#ifndef RILL_VECTOR
#define RILL_VECTOR

#include <cstddef>
#include <initializer_list>

namespace rill {

    template <typename V> class vector {

        protected:
        V *    _members;
        size_t _length;
        size_t _capacity;

        public:
        vector ();
        vector ( size_t initial_capacity );
        vector ( std::initializer_list<V> init_list );
        vector ( const vector & that );
        vector ( const vector && that );
        ~vector ();

        size_t length () const;
        vector & reserve ( size_t new_capacity );
        vector & compact ();
        vector & push ( const V & val );
        vector & push_range (
            const vector & that,
            unsigned long start,
            unsigned long length
        );
        vector & pop ();
        const V & head () const;
        const V & tail () const;
        V & head ();
        V & tail ();
        V * data ();
        const V * data () const;
        vector & operator= ( const vector & that );
        vector operator+ ( const vector & that ) const;
        vector & operator+= ( const vector & that );
        bool operator== ( const vector & that );
        bool operator!= ( const vector & that );
        V & operator[] ( size_t index );
        const V & operator[] ( size_t index ) const;

        vector & clear ();

    };

}

#endif

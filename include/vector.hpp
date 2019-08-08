#ifndef RILL_VECTOR
#define RILL_VECTOR

namespace rill {

    template <typename T> class vector {

        protected:
        T * _members;
        unsigned long _size;
        unsigned long _capacity;

        public:
        vector ();
        vector ( const vector<T> & other );
        vector ( vector<T> && other );
        vector ( std::initializer_list init_list );
        ~vector ();

        unsigned long size () const;

        vector & reserve ( unsigned long new_capacity );
        vector & compact ();

        T & operator[] ( unsigned long index );
        const T & operator[] ( unsigned long index ) const;

        vector & push ( const T & item );
        vector & pop ();

        const T & head () const;
        const T & tail () const;
        T & head ();
        T & tail ();

        operator bool () const;

        bool operator== ( const vector<T> & that ) const;
        bool operator!= ( const vector<T> & that ) const;
        vector<T> & operator= ( const vector<T> & that );
        vector<T> & operator= ( vector<T> && that );
        vector<T> operator+ ( const vector<T> & that ) const;
        vector<T> & operator+= ( const vector<T> & that );

    };

}

#endif

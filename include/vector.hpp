#ifndef RILL_VECTOR
#define RILL_VECTOR

namespace rill {

    template <typename T> class vector {

        protected:
        T *          _items;
        unsigned int _length;
        unsigned int _capacity;

        public:
        vector ();
        vector ( unsigned int initial_capacity );
        vector ( const vector<T> & other );
        vector ( vector<T> && other );
        ~vector ();

        unsigned long size () const;
        operator bool () const;

        vector<T> & reserve ( unsigned int new_capacity );
        vector<T> & compact ();

        vector<T> & push ( const T & item );
        vector<T> & pop ();

        T & operator[] ( unsigned int index );
        const T & operator[] ( unsigned int index ) const;

        vector<T> operator+ ( const vector<T> & other ) const;
        vector<T> & operator+= ( const vector<T> & other );

        vector<T> & operator= ( const vector<T> & other );

        bool operator== ( const vector<T> & other ) const;
        bool operator!= ( const vector<T> & other ) const;

        vector<T> & clear ();

    };

};

#endif

#ifndef RILL_VECTOR
#define RILL_VECTOR

#define RILL_VECTOR_DEFAULT_SIZE  8
#define RILL_VECTOR_RESIZE_FACTOR 2.0

namespace rill {

    template <typename T> class vector {

        protected:
        T * _items;
        unsigned long _len;
        unsigned long _cap;

        vector<T> & resize ( unsigned long new_size );

        public:
        vector ();
        vector ( unsigned long init_cap );
        vector ( std::initializer_list<T> list );
        vector ( const vector & other );
        vector ( vector && other );
        ~vector ();

        unsigned long length () const;
        vector<T> & reserve ( unsigned long new_cap );
        vector<T> & compact ();

        vector<T> & push ( const T & item );
        vector<T> & pop ();

        bool operator== ( const vector<T> & other ) const;
        bool operator!= ( const vector<T> & other ) const;
        T & operator[] ( unsigned long index );
        const T & operator[] ( unsigned long index ) const;
        vector<T> operator+ ( const vector<T> & other ) const;
        vector<T> & operator+= ( const vector<T> & other );

        vector<T> & reverse ();
        vector<T> & empty ();

    };

};

#endif

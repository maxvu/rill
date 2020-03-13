#ifndef RILL_VECTOR
#define RILL_VECTOR

namespace rill {

    template <typename T>
    class vector {

        protected:
            T * _data;

        public:
            vector ();
            vector ( size_t init_cap );
            vector ( const vector & that );
            vector ( vector && that );
            ~vector ();

            size_t length () const;
            vector & reserve ( size_t new_cap );
            vector & compact ();

            vector<T> & operator= ( const vector<T> & that );
            vector<T> & operator= ( vector<T> && that );

            vector<T> & operator+= ( const vector<T> & that );

            vector<T> operator+ ( const vector<T> & that );

            bool operator== ( const vector<T> & that ) const;
            bool operator!= ( const vector<T> & that ) const;

            T & operator[] ( size_t index );
            const T & operator[] ( size_t index ) const;

            vector<T> & push ( const T & item );
            vector<T> & pop ();

            vector<T> & shift ();
            vector<T> & unshift ( const T & item );

            vector<T> & reverse ();
            vector<T> & clear ();

    };

}

#endif

#ifndef RILL_SLAB
#define RILL_SLAB

namespace rill {

    template <typename T> class Slab {

        protected:
            T *    _members;
            size_t _length;

            Slab ( size_t length );
            Slab ( const Slab<T> & that );
            Slab ( Slab<T> && that );

        public:
            ~Slab ();

            operator T * ();
            operator const T * () const;
            T & operator[] ( size_t index );
            const T & operator[] ( size_t index ) const;

    };

}

#endif

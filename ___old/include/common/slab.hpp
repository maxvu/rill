#ifndef RILL_SLAB
#define RILL_SLAB

namespace rill {

     template <typename T> class slab {

        protected:

        T *           _buffer;
        unsigned long _size;

        public:

        slab ( unsigned long size );
        slab ( const slab & other );
        slab ( slab && other );
        ~slab ();

        operator T * ();
        operator const T * () const;
        unsigned long size () const;
        slab<T> & resize ( unsigned long new_size );
        slab<T> & operator= ( const slab & other );
        slab<T> & operator= ( slab && other );

    };

}

#endif

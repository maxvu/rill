#ifndef RILL_BUFFER
#define RILL_BUFFER

namespace rill {

    template <typename T> class buffer {

        protected:
        T *           _data;
        unsigned long _size;

        public:
        buffer ( unsigned long init_cap );
        buffer ( const buffer & that );
        buffer ( buffer && that );
        ~buffer ();

        unsigned long size () const;

        operator T * ();
        operator const T * () const;

        buffer<T> & resize ( unsigned long new_size );

    };

}

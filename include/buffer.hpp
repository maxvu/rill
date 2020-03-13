#ifndef RILL_BUFFER
#define RILL_BUFFER

namespace rill {

    template <typename T>
    class buffer {

        private:
            T *    _data;
            size_t _len;

        protected:
            buffer ();
            buffer ( size_t init_cap );
            buffer ( const buffer & that );
            buffer ( buffer && that );
            ~buffer ();

        public:
            operator T * ();
            operator const T * () const;
            size_t length () const;

            buffer & operator= ( const buffer<T> & that );
            buffer & operator= ( const buffer<T> && that );

            buffer & resize ( size_t new_len );

    };

}

#endif

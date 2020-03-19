#ifndef RILL_REFCOUNTED
#define RILL_REFCOUNTED

namespace rill {

    template <typename T> refcounted {

        private:

            size_t _refcount;

        public:

            refcounted ();

            T & ref ();
            void deref ();


    };

}

#endif

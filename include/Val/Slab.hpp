#ifndef RILL_VAL_SLAB
#define RILL_VAL_SLAB

#include <cstddef>

namespace Rill {

    template <typename T> class Slab {

        protected:

        T * data;
        size_t capacity;

        public:

        Slab ( size_t capacity );
        Slab ( const Slab & other );

        size_t capcacity () const;

        Slab & resize ( size_t new_capacity );
        Slab & reserve ( size_t min_capacity );

        T & operator[] ( size_t index );
        const T & operator[] ( size_t index ) const;

    };

}

#endif

#ifndef RILL_VAL_VECTOR
#define RILL_VAL_VECTOR

#include "Val/Ref.hpp"
#include "Val/Val.hpp"

#include <cstddef>

#define RILL_VAL_VECTOR_MINSIZE 16
#define RILL_VAL_VECTOR_DEFAULTSIZE 16
#define RILL_VAL_VECTOR_GROWTHCOEFF 2.0

namespace Rill {

    class Vector : public Val {

        protected:

        Slab<Ref> vals;
        size_t len;

        public:

        Vector ();
        Vector ( size_t initial_capacity );
        Vector ( const Vector & other );
        ~Vector ();

        size_t length () const;
        size_t capacity () const;

        Vector & reserve ( size_t min_capacity );
        Vector & compact ();

        Val & operator[] ( size_t index );
        const Val & operator[] ( size_t index ) const;

        Vector & push ( const Val & val );
        void pop ();
        Vector & fill ( const Val & val, size_t length );

        Vector & clear ();

    };

}

#endif

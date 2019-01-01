#ifndef RILL_VAL_VEC
#define RILL_VAL_VEC

#include "Val/Val.hpp"

#include <cstddef>
#include <vector>

namespace Rill {

    class Vec : public Refcounted {

        protected:

        Val * vals;
        size_t len;
        size_t cap;

        public:

        Vec ();
        Vec ( const Vec & other );
        ~Vec ();

        Vec & operator= ( const Vec & other );
        bool operator== ( const Vec & other ) const;
        bool operator!= ( const Vec & other ) const;
        Vec & operator+= ( const Vec & other );

        Val & operator[] ( size_t index );
        const Val & operator[] ( size_t index ) const;

        size_t length () const;
        Vec & reserve ( size_t new_capacity );
        Vec & compact ();

        Vec & push ( const Val & item );
        Vec & pop ( const Val & item );
        Vec & reverse ();

        Val serialize () const;

    };

}

#endif

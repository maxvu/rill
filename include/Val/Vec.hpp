#ifndef RILL_VAL_VEC
#define RILL_VAL_VEC

#include "Val/Ref.hpp"
#include "Val/Val.hpp"

#include <cstddef>
#include <initializer_list>

#define RILL_VAL_VEC_MINSIZE 16
#define RILL_VAL_VEC_DEFAULTSIZE 16
#define RILL_VAL_VEC_GROWTHCOEFF 2.0

namespace Rill {

    class Vec : public Val {

        protected:

        Slab<Ref> vals;
        size_t len;

        public:

        Vec ();
        Vec ( size_t initial_capacity );
        Vec ( std::initializer_list<Ref> vals );
        Vec ( const Vec & other );
        ~Vec ();

        Val & lease ();
        int release ();
        Val & exclude ();
        Val * clone () const;
        operator bool () const;
        bool contains ( const Val * needle );

        size_t length () const;
        size_t capacity () const;

        Vec & reserve ( size_t min_capacity );
        Vec & compact ();

        Val & operator[] ( size_t index );
        const Val & operator[] ( size_t index ) const;

        Vec & push ( const Val & val );
        void pop ();

        Vec & fill ( const Val & val, size_t length );

        Vec & clear ();

    };

}

#endif

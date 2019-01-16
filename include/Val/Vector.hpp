#ifndef RILL_VAL_VECTOR
#define RILL_VAL_VECTOR

#include "Val/Refcounted.hpp"

#define RILL_RVEC_MINSIZ 4
#define RILL_RVEC_DEFSIZ 12
#define RILL_RVEC_GROWTH 2.0

namespace Rill {
namespace Val {

    class Vector : public Refcounted {

        protected:

        Val * vals;
        size_t len_;
        size_t cap_;

        public:

        Vector ();
        Vector ( const Vector & that );
        ~Vector ();

        size_t length () const;

        Vector & reserve ( size_t cap );
        Vector & compact ();

        Vector & operator= ( const Vector & that );
        Vector & operator+= ( const Vector & that );
        bool operator== ( const Vector & that );

        Vector & push ( const Val & val );
        Vector & pop ();

        Val & operator[] ( size_t index );
        const Val & operator[] ( size_t index ) const;

        Vector & fillWith ( const Val & item, size_t n );
        Vector & reverse ();
        Vector & clear ();

    };

}
}

#endif

#ifndef RILL_BIGINT
#define RILL_BIGINT

#include <gmp.h>

namespace rill {

    class bigint;

    class bigfloat {

        protected:

        mpf_t _mpf;

        public:

        bigfloat ();
        bigfloat ( const bigfloat & other );
        bigfloat ( const string & other );
        bigfloat ( double d );
        bigfloat ( const bigint & bi );
        bigfloat ( int i );
        ~bigfloat ();

        bigfloat neg () const;
        bigfloat abs () const;
        bigfloat pow () const;

        bigfloat operator+ ( const bigfloat & bf ) const;
        bigfloat operator- ( const bigfloat & bf ) const;
        bigfloat operator* ( const bigfloat & bf ) const;
        bigfloat operator/ ( const bigfloat & bf ) const;

        bigfloat & operator+= ( const bigfloat & bf );
        bigfloat & operator-= ( const bigfloat & bf );
        bigfloat & operator*= ( const bigfloat & bf );
        bigfloat & operator/= ( const bigfloat & bf );

        bigfloat operator+ ( double d ) const;
        bigfloat operator- ( double d ) const;
        bigfloat operator* ( double d ) const;
        bigfloat operator/ ( double d ) const;

        bigfloat & operator+= ( double d );
        bigfloat & operator-= ( double d );
        bigfloat & operator*= ( double d );
        bigfloat & operator/= ( double d );

        bool operator> ( const bigfloat & bf ) const;
        bool operator< ( const bigfloat & bf ) const;
        bool operator== ( const bigfloat & bf ) const;
        bool operator!= ( const bigfloat & bf ) const;
        bool operator>= ( const bigfloat & bf ) const;
        bool operator<= ( const bigfloat & bf ) const;

    };

}

#endif

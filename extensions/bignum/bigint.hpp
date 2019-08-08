#ifndef RILL_BIGINT
#define RILL_BIGINT

#include <gmp.h>

namespace rill {

    class bigfloat;

    class bigint {

        protected:

        mpz_t _mpz;

        public:

        static bigint random ( unsigned long bit_count );

        bigint ();
        bigint ( const bigint & other );
        bigint ( const bigfloat & other );
        bigint ( const string & other );
        bigint ( const string & other, int base );
        bigint ( unsigned long u );
        bigint ( long i );
        bigint ( double d );
        ~bigint ();

        bool fits_long () const;
        bool fits_ulong () const;
        long to_long () const;
        unsigned long to_ulong () const;
        unsigned double to_double () const;
        string to_string () const;
        string to_string ( int base ) const;

        bigint neg () const;
        bigint abs () const;
        bigint pow ( const bigint & power ) const;
        bigint sqrt () const;
        bigint root ( unsigned long int r );
        bigint choose ( unsigned long k );

        bool prime () const;
        bool odd () const;
        bool even () const;
        bigint fact () const;
        unsigned long positive () const;
        unsigned long negative () const;

        bool operator>  ( const bigint & other ) const;
        bool operator== ( const bigint & other ) const;
        bool operator<  ( const bigint & other ) const;
        bool operator>= ( const bigint & other ) const;
        bool operator<= ( const bigint & other ) const;
        bool operator!= ( const bigint & other ) const;

        bool operator>  ( long i ) const;
        bool operator== ( long i ) const;
        bool operator<  ( long i ) const;
        bool operator>= ( long i ) const;
        bool operator<= ( long i ) const;
        bool operator!= ( long i ) const;

        bigint & operator+= ( const bigint & other );
        bigint & operator-= ( const bigint & other );
        bigint & operator*= ( const bigint & other );
        bigint & operator/= ( const bigint & other );
        bigint & operator%= ( const bigint & other );

        bigint & operator+= ( long i );
        bigint & operator-= ( long i );
        bigint & operator*= ( long i );
        bigint & operator/= ( long i );
        bigint & operator%= ( long i );

        bigint operator+ ( const bigint & other ) const;
        bigint operator- ( const bigint & other ) const;
        bigint operator* ( const bigint & other ) const;
        bigint operator/ ( const bigint & other ) const;
        bigint operator% ( const bigint & other ) const;

        bigint operator+ ( long i ) const;
        bigint operator- ( long i ) const;
        bigint operator* ( long i ) const;
        bigint operator/ ( long i ) const;
        bigint operator% ( long i ) const;

    };

}

#endif

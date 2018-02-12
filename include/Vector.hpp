#ifndef RILL_VECTOR
#define RILL_VECTOR

#define RILL_VECTOR_MINSIZE 2
#define RILL_VECTOR_DEFAULTSIZE 12
#define RILL_VECTOR_GROWTHCOEFF 1.8

#include <cstddef>
#include <initializer_list>

#include "Error.hpp"

using std::initializer_list;

namespace Rill {

    template <typename T> class Vector {

        protected:

        T * data;
        size_t len;
        size_t cap;

        Vector<T> & resize ( size_t newCap ) {
            T * newData = new T[ newCap ];
            for ( size_t i = 0; i < this->len; i++ )
                newData[ i ] = this->data[ i ];
            delete[] this->data;
            this->data = newData;
            this->cap = newCap;
            return *this;
        }

        public:

        Vector () : Vector( RILL_VECTOR_DEFAULTSIZE ) {

        }

        Vector ( size_t initCap ) : len( 0 ), cap( initCap ) {
            if ( this->cap <= RILL_VECTOR_MINSIZE )
                this->cap = RILL_VECTOR_DEFAULTSIZE;
            this->data = new T[ this->cap ];
        }

        Vector ( std::initializer_list<T> init ) : Vector( init.size() ) {
            const T * item = init.begin();
            while ( item != init.end() )
                this->push( *item++ );
        }

        Vector ( const Vector & other ) : Vector( other.getLength() ) {
            for ( size_t i = 0; i < other.getLength(); i++ )
                this->data[ i ] = other.data[ i ];
        }

        ~Vector () {
            delete[] data;
        }

        Vector<T> & operator= ( const Vector<T> & other ) {
            this->reserve( other.getLength() );
            for ( size_t i = 0; i < other.len; i++ )
                this->data[ i ] = other.data[ i ];
            return *this;
        }

        bool operator== ( const Vector<T> & other ) const {
            if ( this->len != other.len )
                return false;
            for ( size_t i = 0; i < other.len; i++ )
                if ( this->data[ i ] != other.data[ i ] )
                    return false;
            return true;
        }

        bool operator!= ( const Vector<T> & other ) const {
            return !( *this == other );
        }

        Vector<T> & push ( const T & item ) {
            if ( this->len == this->cap )
                this->reserve( this->cap * RILL_VECTOR_GROWTHCOEFF );
            this->data[ len ] = item;
            this->len++;
            return *this;
        }

        T pop () {
            if ( !this->len )
                throw InternalError( "Pop()'ing an empty Vector." );
            T copy = this->data[ this->len ];
            this->len--;
            return copy;
        }

        Vector<T> & operator+= ( const Vector<T> & other ) {
            this->reserve( this->len + other.len );
            for ( size_t i = 0; i < other.len; i++ ) {
                this->push( other[ i ] );
            }
            return *this;
        }

        Vector<T> operator+ ( const Vector<T> & other ) const {
            Vector<T> copy = *this;
            copy += other;
            return copy;
        }

        const T & operator[] ( size_t idx ) const {
            if ( idx >= this->len )
                throw InternalError( "OOB index access on Vector." );
            return this->data[ idx ];
        }

        T & operator[] ( size_t idx ) {
            if ( idx >= this->len )
                throw InternalError( "OOB index access on Vector." );
            return this->data[ idx ];
        }

        Vector<T> & reserve ( size_t newCap ) {
            if ( newCap <= this->cap )
                return *this;
            return this->resize( newCap );
        }

        Vector<T> & compact () {
            if ( this->len == this->cap )
                return *this;
            return this->resize( this->len );
        }

        size_t getCapacity () const {
            return this->cap;
        }

        size_t getLength () const {
            return this->len;
        }

        operator bool () const {
            return this->len;
        }

    };

};

#endif

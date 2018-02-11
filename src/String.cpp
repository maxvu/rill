#include "String.hpp"

namespace Rill {

    String & String::__resize ( size_t newCap ) {
        char * newBuf = new char[ newCap + 1 ];
        strncpy( newBuf, this->buf, this->len );
        delete[] this->buf;
        this->buf = newBuf;
        this->cap = newCap;
        return *this;
    }

    String::String (
        size_t initCap
    ) : buf( nullptr ), len( 0 ), cap( initCap ) {
        this->buf = new char[ this->cap + 1 ];
        memset( this->buf, 0, this->cap + 1 );
    }

    String::String () : String( RILL_STRING_DEFAULTLEN ) {

    }

    String::String ( const char * cstr ) : String() {
        *this = cstr;
    }

    String::String ( const String & other ) : String( other.len ) {
        *this = other;
    }

    String::String (
        const String && other
    ) : buf( other.buf ), len( other.len ), cap( other.cap ) {

    }

    String::~String () {
        delete[] this->buf;
    }

    size_t String::getLength () const {
        return this->len;
    }

    size_t String::getCapacity () const {
        return this->cap;
    }

    String & String::operator= ( const String & other ) {
        this->reserve( other.len );
        strncpy( this->buf, other.buf, other.len );
        this->len = other.len;
        return *this;
    }

    String & String::operator= ( const char * other ) {
        size_t otherLen = strlen( other );
        this->reserve( otherLen );
        strncpy( this->buf, other, otherLen );
        this->len = otherLen;
        return *this;
    }

    bool String::operator== ( const String & other ) const {
        if ( this->len != other.len )
            return false;
        return strcmp( this->buf, other.buf ) == 0;
    }

    bool String::operator== ( const char * cstr ) const {
        return strncmp( this->buf, cstr, this->len ) == 0;
    }

    bool String::operator!= ( const String & other ) const {
        return !( *this == other );
    }

    bool String::operator!= ( const char * cstr ) const {
        return !( *this == cstr );
    }

    bool String::operator< ( const String & other ) const {
        return strcmp( this->buf, other.buf ) < 0;
    }

    bool String::operator> ( const char * cstr ) const {
        return strcmp( this->buf, cstr ) > 0;
    }

    bool String::operator<= ( const String & other ) const {
        return strcmp( this->buf, other.buf ) <= 0;
    }

    bool String::operator>= ( const char * cstr ) const {
        return strcmp( this->buf, cstr ) >= 0;
    }

    String & String::operator+= ( const String & other ) {
        this->reserve( this->len + other.len );
        strcpy( this->buf + this->len, other.buf );
        this->len += other.len;
        return *this;
    }

    String & String::operator+= ( const char * cstr ) {
        size_t cstrLen = strlen( cstr );
        this->reserve( this->len + cstrLen );
        strncpy( this->buf + this->len, cstr, cstrLen );
        this->len += cstrLen;
        return *this;
    }

    String String::operator+ ( const String & other ) const {
        String tmp = *this;
        tmp += other;
        return tmp;
    }

    String String::operator+ ( const char * cstr ) const {
        return String( *this ) += cstr;
    }

    char & String::operator[] ( size_t idx ) {
        if ( idx >= this->len )
            throw "TODO: real exception.";
        return this->buf[ idx ];
    }

    const char & String::operator[] ( size_t idx ) const {
        if ( idx >= this->len )
            throw "TODO: real exception.";
        return this->buf[ idx ];
    }

    String & String::reserve ( size_t newCap ) {
        if ( newCap <= this->cap )
            return *this;
        return this->__resize( newCap );
    }

    String & String::compact () {
        if ( this->len <= RILL_STRING_DEFAULTLEN )
            return *this;
        if ( this->len == this->cap )
            return *this;
        return this->__resize( this->len );
    }

    const char * String::find ( const char * substr ) const {
        return strstr( this->buf, substr );
    }

    String::operator const char * () const {
        return this->buf;
    }

};

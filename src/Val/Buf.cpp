#include "Val/Buf.hpp"

#include <cstring>

namespace Rill {

Buf & Buf::resize ( size_t new_size ) {
    uint8_t * new_bytes = new uint8_t[ new_size + 1 ];
    memcpy( new_bytes, this->bytes, this->len + 1 );
    delete[] this->bytes;
    this->bytes = new_bytes;
    this->cap = new_size;
    return *this;
}

Buf::Buf () : Buf( RILL_VAL_BUF_DEFAULTSIZE ) {

}

Buf::Buf ( size_t initial_capacity ) {
    if ( initial_capacity < RILL_VAL_BUF_MINSIZE )
        initial_capacity = RILL_VAL_BUF_MINSIZE;
    this->bytes = new uint8_t[ initial_capacity + 1 ];
    this->len = 0;
    this->cap = initial_capacity;
}

Buf::Buf ( const Buf & other ) : Buf( other.len * RILL_VAL_BUF_GROWTHC ) {
    *this = other;
}

Buf::~Buf () {
    if ( this->bytes )
        delete[] this->bytes;
}

Buf::operator bool () const {
    return this->len;
}

Buf & Buf::operator= ( const Buf & other ) {
    return this->clear() += other;
}

Buf & Buf::operator+= ( const Buf & other ) {
    return this->reserve( this->len + other.len ).asBytes().cat(
        other.bytes,
        other.len
    );
}

bool Buf::operator== ( const Buf & other ) const {
    return const_cast<Buf*>(this)->asBytes().cmp( other.bytes, other.len ) == 0;
}

bool Buf::operator!= ( const Buf & other ) const {
    return !( *this == other );
}

size_t Buf::length () const {
    return this->len;
}

Buf & Buf::reserve ( size_t new_capacity ) {
    if ( this->cap >= new_capacity )
        return *this;
    return this->resize( new_capacity );
}

Buf & Buf::compact () {
    size_t target = this->len;
    if ( target < RILL_VAL_BUF_MINSIZE )
        target = RILL_VAL_BUF_MINSIZE;
    if ( this->cap == target )
        return *this;
    return this->resize( target );
}

Buf & Buf::clear () {
    this->len = 0;
    this->bytes[ 0 ] = 0;
    return *this;
}

BufCharView & Buf::asChars () {
    return reinterpret_cast<BufCharView&>( *this );
}

BufBytesView & Buf::asBytes () {
    return reinterpret_cast<BufBytesView&>( *this );
}

BufUTF8View & Buf::asUTF8 () {
    return reinterpret_cast<BufUTF8View&>( *this );
}

const BufBytesView & Buf::asBytes () const {
    Buf & self = const_cast<Buf&>( *this );
    BufBytesView & convertedSelf = reinterpret_cast<BufBytesView&>( self );
    return const_cast<const BufBytesView&>( convertedSelf );
}

const BufCharView & Buf::asChars () const {
    Buf & self = const_cast<Buf&>( *this );
    BufCharView & convertedSelf = reinterpret_cast<BufCharView&>( self );
    return const_cast<const BufCharView&>( convertedSelf );
}

const BufUTF8View & Buf::asUTF8 () const {
    Buf & self = const_cast<Buf&>( *this );
    BufUTF8View & convertedSelf = reinterpret_cast<BufUTF8View&>( self );
    return const_cast<const BufUTF8View&>( convertedSelf );
}


BufBytesView & BufBytesView::set ( const uint8_t * mem, size_t mem_len ) {
    if ( !mem )
        throw std::runtime_error( "null pointer provided to BufBytesView::set");
    this->clear().reserve( mem_len );
    if ( !mem_len )
        return *this;
    memcpy( this->bytes, mem, mem_len );
    this->len = mem_len;
    this->bytes[ this->len ] = 0;
    return *this;
}

BufBytesView & BufBytesView::cat ( const uint8_t * mem, size_t mem_len ) {
    if ( !mem )
        throw std::runtime_error( "null pointer provided to BufBytesView::cat");
    if ( this->cap <= this->len + mem_len )
        this->reserve( ( this->len + mem_len ) * RILL_VAL_BUF_GROWTHC );
    if ( !mem_len )
        return *this;
    memcpy( this->bytes + this->len, mem, mem_len );
    this->len += mem_len;
    this->bytes[ this->len ] = 0;
    return *this;
}

int BufBytesView::cmp ( const uint8_t * mem, size_t mem_len ) const {
    if ( !mem )
        throw std::runtime_error( "null pointer provided to BufBytesView::cmp");
    return memcmp(
        this->bytes,
        mem,
        this->len < mem_len ? this->len : mem_len
    );
}

uint8_t & BufBytesView::operator[] ( size_t index ) {
    return this->bytes[ index ];
}

const uint8_t & BufBytesView::operator[] ( size_t index ) const {
    return this->bytes[ index ];
}

BufCharView & BufCharView::operator= ( const char * cstr ) {
    if ( !cstr )
        throw std::runtime_error(
            "null pointer provided to BufCharView::operator="
        );
    size_t cstr_len = strlen( cstr );
    if ( cstr_len )
        reinterpret_cast<BufBytesView&>( this->clear() ).cat(
            reinterpret_cast<const uint8_t*>( cstr ),
            cstr_len
        );
    return *this;
}

BufCharView & BufCharView::operator+= ( const char * cstr ) {
    if ( !cstr )
        throw std::runtime_error(
            "null pointer provided to BufCharView::operator="
        );
    size_t cstr_len = strlen( cstr );
    if ( cstr_len )
        reinterpret_cast<BufBytesView&>( *this ).cat(
            reinterpret_cast<const uint8_t*>( cstr ),
            cstr_len
        );
    return *this;
}

bool BufCharView::operator== ( const char * cstr ) const {
    return strncmp(
        reinterpret_cast<const char*>( this->bytes ),
        cstr,
        this->len
    );
}

bool BufCharView::operator!= ( const char * cstr ) const {
    return !( *this == cstr );
}

char & BufCharView::operator[] ( size_t index ) {
    return reinterpret_cast<char*>( this->bytes )[ index ];
}

const char & BufCharView::operator[] ( size_t index ) const {
    return reinterpret_cast<const char*>( this->bytes )[ index ];
}

}
